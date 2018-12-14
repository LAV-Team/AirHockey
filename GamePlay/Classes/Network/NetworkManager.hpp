#ifndef __NETWORK_MANAGER_INCLUDED__
#define __NETWORK_MANAGER_INCLUDED__

#include "Network.hpp"

namespace HockeyNet
{
	class NetworkManager;
	typedef boost::shared_ptr<NetworkManager> NetworkManagerPtr;

	struct StrikerInfo {
		short int x;
		short int y;
	};

	struct PuckInfo {
		short int x;
		short int y;
		float vX;
		float vY;
	};

	typedef boost::function<void(std::string const&)> OnStartHandler;
	typedef boost::function<void()> OnStopHandler;
	typedef boost::function<void(StrikerInfo const&)> OnStrikerHandler;
	typedef boost::function<void(PuckInfo const&)> OnPuckHandler;

	static std::string const STRIKER_DATA{ "DS" };
	static std::string const PUCK_DATA{ "DP" };

	class NetworkException
		: public std::exception
	{
	public:
		explicit NetworkException(std::string const& message);
		char const* what() const;
	private:
		std::string message_;
	};

	class NetworkManager
		: public boost::enable_shared_from_this<NetworkManager>
		, boost::noncopyable
	{
	public:
		// Network manager creator
		static NetworkManagerPtr Create();

		// To connect to the server (you automatically become available to connect from others)
		bool Connect(boost::asio::ip::tcp::endpoint const& ep, std::string username);
		// Disconnect from server
		void Disconnect();

		// Get list of free (available to connect) users
		std::list<std::string> GetFreeUsers();
		// Wait random enemy
		void WaitEnemy(std::string username = std::string{});
		// Stop waiting random enemy
		void CancelWaiting();
		// Stop started session of game
		void Cancel();

		// Send striker data to enemy
		void Send(StrikerInfo strikerInfo);
		// Send puck data to enemy
		void Send(PuckInfo puckInfo);

		// Set listener on game start
		void SetStartHandler(OnStartHandler onStartHandler);
		// Set listener on game stop
		void SetStopHandler(OnStopHandler onStopHandler);
		// Set listener on striker data from enemy
		void SetStrikerHandler(OnStrikerHandler onStrikerHandler);
		// Set listener on puck data from enemy
		void SetPuckHandler(OnPuckHandler onPuckHandler);
		// Set listener on server disconnect
		void SetCloseHandler(OnCloseHandler onCloseHandler);

	private:
		typedef NetworkManager SelfType;

		NetworkPtr network_;
		OnStartHandler onStartHandler_;
		OnStopHandler onStopHandler_;
		OnStrikerHandler onStrikerHandler_;
		OnPuckHandler onPuckHandler_;
		std::string freeUsers_;
		std::condition_variable freeUsersWaiting_;

		NetworkManager();

		void Send_(void* data, size_t length, std::string prefix = std::string{});

		void OnError_(boost::system::error_code const& error);
		void OnAnswer_(std::string const& answer);

	};
};

#endif // __NETWORK_MANAGER_INCLUDED__