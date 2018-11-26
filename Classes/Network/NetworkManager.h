#ifndef __NETWORK_MANAGER_INCLUDED__
#define __NETWORK_MANAGER_INCLUDED__

#include "lib/General.hpp"
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
	};

	class NetworkManager
		: public boost::enable_shared_from_this<NetworkManager>
		, boost::noncopyable
	{
	public:
		static NetworkManagerPtr Create();

		bool Connect(boost::asio::ip::tcp::endpoint const& ep, std::string username);
		void Disconnect();

		std::vector<std::string> GetFreeUsers();
		void WaitEnemy(std::string username = std::string{});
		void CancelWaiting();
		void Cancel();

		void Send(StrikerInfo strikerInfo);
		void Send(PuckInfo puckInfo);

		void SetStartHandler(OnStartHandler onStartHandler);
		void SetStopHandler(OnStopHandler onStopHandler);
		void SetStrikerHandler(OnStrikerHandler onStrikerHandler);
		void SetPuckHandler(OnPuckHandler onPuckHandler);
		void SetCloseHandler(OnCloseHandler onCloseHandler);

	private:
		typedef NetworkManager SelfType;

		NetworkPtr network_;
		OnStartHandler onStartHandler_;
		OnStopHandler onStopHandler_;
		OnStrikerHandler onStrikerHandler_;
		OnPuckHandler onPuckHandler_;

		NetworkManager();

		void Send_(void* data, size_t length, std::string prefix = std::string{});

		void OnError_(boost::system::error_code const& error);
		void OnAnswer_(std::string const& answer);

	};
};

#endif // __NETWORK_MANAGER_INCLUDED__
