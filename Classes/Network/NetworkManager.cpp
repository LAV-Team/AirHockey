#include "NetworkManager.h"

HockeyNet::NetworkManagerPtr HockeyNet::NetworkManager::Create()
{
	NetworkManagerPtr networkManager{ new NetworkManager {} };
	networkManager->network_->SetErrorHandler(boost::bind(&NetworkManager::OnError_, networkManager, _1));
	networkManager->network_->SetAnswerHandler(boost::bind(&NetworkManager::OnAnswer_, networkManager, _1));
	return networkManager;
}

HockeyNet::NetworkManager::NetworkManager()
	: network_{ Network::Create() }
{}

bool HockeyNet::NetworkManager::Connect(boost::asio::ip::tcp::endpoint const& ep, std::string username)
{
	return network_->Connect(ep);
}

void HockeyNet::NetworkManager::Disconnect()
{
	network_->Disconnect();
}

std::vector<std::string> HockeyNet::NetworkManager::GetFreeUsers()
{
	std::vector<std::string> result{};
	std::string base{ "Example_" };
	for (size_t i{ 0U }; i < 30; ++i) {
		result.push_back(base + std::to_string(i));
	}
	return result;
}

void HockeyNet::NetworkManager::WaitEnemy(std::string username)
{
	network_->Send(WAIT_SESSION + username);
}

void HockeyNet::NetworkManager::CancelWaiting()
{
	network_->Send(STOP_WAITING_SESSION);
}

void HockeyNet::NetworkManager::Cancel()
{
	network_->Send(STOP_SESSION);
}

void HockeyNet::NetworkManager::Send(StrikerInfo strikerInfo)
{
	Send_(&strikerInfo, sizeof(strikerInfo), STRIKER_DATA);
}

void HockeyNet::NetworkManager::Send(PuckInfo puckInfo)
{
	Send_(&puckInfo, sizeof(puckInfo), PUCK_DATA);
}

void HockeyNet::NetworkManager::SetStartHandler(OnStartHandler onStartHandler)
{
	onStartHandler_ = onStartHandler;
}

void HockeyNet::NetworkManager::SetStopHandler(OnStopHandler onStopHandler)
{
	onStopHandler_ = onStopHandler;
}

void HockeyNet::NetworkManager::SetStrikerHandler(OnStrikerHandler onStrikerHandler)
{
	onStrikerHandler_ = onStrikerHandler;
}

void HockeyNet::NetworkManager::SetPuckHandler(OnPuckHandler onPuckHandler)
{
	onPuckHandler_ = onPuckHandler;
}

void HockeyNet::NetworkManager::SetCloseHandler(OnCloseHandler onCloseHandler)
{
	network_->SetCloseHandler(onCloseHandler);
}

void HockeyNet::NetworkManager::Send_(void* data, size_t length, std::string prefix)
{
	network_->Send(prefix + std::string{ static_cast<char*>(data), length });
}

void HockeyNet::NetworkManager::OnError_(boost::system::error_code const& error)
{
	throw NetworkException{ error.message() };
}

void HockeyNet::NetworkManager::OnAnswer_(std::string const& answer)
{
	if (answer.size() < 2) {
		return;
	}

	std::string command{ answer.begin(), answer.begin() + 2 };
	std::string data{ answer.begin() + 2, answer.end() };

	if (command == STRIKER_DATA) {
		onStrikerHandler_(*(StrikerInfo*)(data.data()));
	}
	else if (command == PUCK_DATA) {
		onPuckHandler_(*(PuckInfo*)(data.data()));
	}
	else if (command == SESSION_BEGIN) {
		if (onStartHandler_) {
			onStartHandler_(data);
		}
	}
	else if (command == SESSION_END) {
		if (onStopHandler_) {
			onStopHandler_();
		}
	}
}
