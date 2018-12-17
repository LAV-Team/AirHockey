#include "Server.hpp"

HockeyNet::ServerPtr HockeyNet::Server::Create(unsigned short port)
{
	ServerPtr server{ new Server{ port } };
	return server;
}

HockeyNet::Server::Server(unsigned short port)
	: isStarted_{ false }
	, service_{}
	, serviceThread_{}
	, acceptor_{ service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) }
	, freeClients_{}
	, waitingClients_{}
	, busyClients_{}
{}

void HockeyNet::Server::Start()
{
	if (isStarted_) {
		return;
	}
	isStarted_ = true;

	CreateTransceiver_();
	serviceThread_ = std::thread{ boost::bind(&boost::asio::io_service::run, &service_) };
}

void HockeyNet::Server::Stop()
{
	if (!isStarted_) {
		return;
	}
	isStarted_ = false;

	for (auto& client : busyClients_) {
		client->Close();
	}
	for (auto& client : waitingClients_) {
		client->Close();
	}
	for (auto& client : freeClients_) {
		client->Close();
	}
	service_.stop();
	serviceThread_.join();
}

void HockeyNet::Server::CreateTransceiver_()
{
	ClientPtr client{ Client::Create(service_) };
	client->SetErrorHandler(BIND(ErrorHandler_, client, _1));
	client->SetAnswerHandler(BIND(AnswerHandler_, client, _1));
	client->SetCloseHandler(BIND(CloseHandler_, client));
	acceptor_.async_accept(client->Sock(), BIND(AcceptHandler_, client, _1));
}

std::string HockeyNet::Server::GenerateSessionId_()
{
	std::string result{};
	srand(static_cast<unsigned int>(time(0)));
	for (size_t i{ 0U }; i < SESSION_ID_LENGTH; ++i) {
		switch (rand() % 5)
		{
		case 0:
		case 1:
			result += 'A' + rand() % 26;
			break;
		case 2:
		case 3:
			result += 'a' + rand() % 26;
			break;
		case 4:
			result += '0' + rand() % 10;
			break;
		}
	}
	return result;
}

void HockeyNet::Server::StartSession_(ClientPtr first, ClientPtr second)
{
	std::string sessionId{ GenerateSessionId_() };

	first->SetSessionId(sessionId);
	first->SetAnotherClient(second);
	second->SetSessionId(sessionId);
	second->SetAnotherClient(first);

	first->Send(SESSION_BEGIN);
	second->Send(SESSION_BEGIN);
	std::cout << "Session " << first->GetShortSessionId() << " started." << std::endl;

	busyClients_.push_back(first);
	busyClients_.push_back(second);
}

bool HockeyNet::Server::StartSession_()
{
	// Get first two clients
	if (waitingClients_.size() < 2) {
		return false;
	}
	auto first{ waitingClients_.front() };
	waitingClients_.pop_front();
	auto second{ waitingClients_.front() };	
	waitingClients_.pop_front();

	// Start session
	StartSession_(first, second);
	return true;
}

bool HockeyNet::Server::StartSession_(ClientPtr client, std::string otherUsername)
{
	// Find users
	auto firstIt{ std::find(freeClients_.begin(), freeClients_.end(), client) };
	if (firstIt == freeClients_.end()) {
		return false;
	}
	auto secondIt{ std::find_if(freeClients_.begin(), freeClients_.end(),
		[&otherUsername](ClientPtr current) { return current->GetUsername() == otherUsername; }
	) };
	if (secondIt == freeClients_.end()) {
		return false;
	}
	
	// Get clients
	auto first{ *firstIt };
	auto second{ *secondIt };
	freeClients_.erase(firstIt);
	freeClients_.erase(secondIt);

	// Start session
	StartSession_(first, second);
	return true;
}

void HockeyNet::Server::StartWaiting_(ClientPtr client)
{
	auto it{ std::find(freeClients_.begin(), freeClients_.end(), client) };
	if (it != freeClients_.end()) {
		freeClients_.erase(it);
		waitingClients_.push_back(client);
		StartSession_();
	}
}

void HockeyNet::Server::StopWaiting_(ClientPtr client)
{
	auto it{ std::find(waitingClients_.begin(), waitingClients_.end(), client) };
	if (it != waitingClients_.end()) {
		waitingClients_.erase(it);
		freeClients_.push_back(client);
	}
}

void HockeyNet::Server::StopSession_(ClientPtr client)
{
	client->Send(SESSION_END);
	client->ClearSessionId();
	client->ClearAnotherClient();
	busyClients_.remove(client);
	freeClients_.push_back(client);
}

void HockeyNet::Server::AcceptHandler_(ClientPtr client, boost::system::error_code const& error)
{
	CreateTransceiver_();

	client->StartReading();
	freeClients_.push_back(client);
}

void HockeyNet::Server::ErrorHandler_(ClientPtr client, boost::system::error_code const& error)
{
	std::cout << client->GetShortSessionId() << ": " << error.message() << std::endl;
}

void HockeyNet::Server::AnswerHandler_(ClientPtr client, std::string const& answer)
{
	// Set username
	if (answer.find(SET_USERNAME) == 0U) {
		client->SetUsername(std::string{ answer.begin() + SET_USERNAME.size(), answer.end() });
		client->Send(OK_ANSWER);
		return;
	}
	// Get free users
	else if (answer == GET_USERNAMES) {
		std::string result{ USERNAMES_LIST };
		for (auto user : freeClients_) {
			result += USERNAMES_SEPARATOR + user->GetUsername();
		}
		client->Send(result);
		return;
	}

	// No another client
	if (client->GetSessionId().empty() || !client->GetAnotherClient()) {
		// Start session with username
		if (answer.find(START_SESSION) == 0U) {
			std::string username{ answer.begin() + START_SESSION.size(), answer.end() };
			StartSession_(client, username);
		}
		// From free to waiting
		else if (answer == WAIT_SESSION) {
			StartWaiting_(client);
			client->Send(OK_ANSWER);
		}
		// From waiting to free
		else if (answer == STOP_WAITING_SESSION) {
			StopWaiting_(client);
			client->Send(OK_ANSWER);
		}
		// Unknown answer from not busy user
		else {
			std::cout << "Answer from empty session id!" << std::endl;
			client->Send(NO_SESSION);
		}
		return;
	}

	// Incorrect session id
	if (client->GetSessionId() != client->GetAnotherClient()->GetSessionId()) {
		std::cout << "Answer from unknown session id: " << client->GetShortSessionId() << "!" << std::endl;
		client->Send(UNKNOWN_SESSION);
		return;
	}

	// Stop session
	if (answer == STOP_SESSION) {
		std::cout << "Session " << client->GetShortSessionId() << " stopped." << std::endl;
		StopSession_(client->GetAnotherClient());
		StopSession_(client);
		return;
	}

	// Transceive message
	std::cout << client->GetShortSessionId() << ": client sent \"" << answer << "\"" << std::endl;
	client->GetAnotherClient()->Send(answer);
}

void HockeyNet::Server::CloseHandler_(ClientPtr client)
{
	// No another client => not busy
	if (client->GetSessionId().empty() || !client->GetAnotherClient()) {
		std::cout << "Some client was disconnected!" << std::endl;
		freeClients_.remove(client);
		waitingClients_.remove(client);
		return;
	}
	busyClients_.remove(client);

	// Incorrect session id
	if (client->GetSessionId() != client->GetAnotherClient()->GetSessionId()) {
		std::cout << "Client with unknown session id was disconnected!" << std::endl;
		return;
	}
	
	// Kick another user from busy to free
	std::cout << "Session " << client->GetShortSessionId() << " stopped." << std::endl;
	StopSession_(client->GetAnotherClient());
}
