#include <iostream>
#include "../../GamePlay/Classes/Network/Network.hpp"

void OnError(boost::system::error_code const& error)
{
	std::cout << error.message() << std::endl;
}

void OnAnswer(std::string const& answer)
{
	if (answer.size() < 2) {
		return;
	}

	std::string command{ answer.begin(), answer.begin() + 2 };
	std::string data{ answer.begin() + 2, answer.end() };

	if (command == HockeyNet::USERNAMES_LIST) {
		std::list<std::string> users{};
		size_t last{ 0U };
		while (last < data.size() && data[last] == HockeyNet::USERNAMES_SEPARATOR) {
			++last;
			size_t newLast{ data.find(HockeyNet::USERNAMES_SEPARATOR, last) };
			users.push_back(data.substr(last, newLast - last));
			last = newLast;
		}
		std::cout << "Free users:" << std::endl;
		for (auto const& user : users) {
			std::cout << user << std::endl;
		}
		return;
	}

	std::cout << answer << std::endl;
}

void OnClose()
{
	std::cout << "Server does't want to talk with you :c" << std::endl;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	std::string buffer{};

	std::cout << "Enter IP (blank for 127.0.0.1): ";
	std::getline(std::cin, buffer);
	std::string address{ buffer.empty() ? "127.0.0.1" : buffer };

	std::cout << "Enter port (blank for 4444): ";
	std::getline(std::cin, buffer);
	unsigned short port{ buffer.empty() ? 4444U : static_cast<unsigned short>(std::stoul(buffer)) };

	std::cout << "Enter username: ";
	std::getline(std::cin, buffer);
	std::string username{ buffer.empty() ? "username" : buffer };

	HockeyNet::NetworkPtr network{ HockeyNet::Network::Create() };
	network->SetErrorHandler(OnError);
	network->SetAnswerHandler(OnAnswer);
	network->SetCloseHandler(OnClose);

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(address), port);
	if (network->Connect(ep)) {
		std::cout << "Connected to " << address << ":" << port << "..." << std::endl;
		network->StartReading();
		network->Send(HockeyNet::SET_USERNAME + username);

		while (std::getline(std::cin, buffer) && network->IsConnected()) {
			if (buffer == "/exit") {
				std::cout << "Stopping..." << std::endl;
				break;
			}
			else if (buffer == "/wait") {
				network->Send(HockeyNet::WAIT_SESSION);
			}
			else if (buffer == "/free") {
				network->Send(HockeyNet::STOP_WAITING_SESSION);
			}
			else if (buffer == "/stop") {
				network->Send(HockeyNet::STOP_SESSION);
			}
			else if (buffer == "/get") {
				network->Send(HockeyNet::GET_USERNAMES);
			}
			else if (buffer == "/user") {
				std::cout << "Enter username: ";
				std::getline(std::cin, buffer);
				std::string username{ buffer.empty() ? "username" : buffer };
				network->Send(HockeyNet::START_SESSION + username);
			}
			else if (!buffer.empty()) {
				network->Send(buffer);
			}
		}
		network->Disconnect();
	}
	else {
		std::cout << "Connection error!" << std::endl;
	}
}
