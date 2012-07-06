#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace wlm {

class WLMFilter {
public:
	void start();

private:
	tcp::socket socket_;
		
}

} // namespace
