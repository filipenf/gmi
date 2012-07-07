#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace wlm {

class WLMFilter {
public:
	WLMFilter(boost::asio::io_service &);
	void start();
	void read_header();

private:
	boost::asio::io_service &io_service_;
	tcp::socket socket_;
};

} // namespace
