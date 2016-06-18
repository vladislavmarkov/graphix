#include <msgpack.hpp>
#include <zmq.hpp>
#include <cassert>

#include "error.hpp"
#include "message.hpp"

namespace gfx_impl{

zmq::message_t wrap(const message &msg){
    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pac(&buffer); pac.pack(msg);
    zmq::message_t zmsg(buffer.size());
    std::memcpy(zmsg.data(), buffer.data(), buffer.size());
    return zmsg;
}

message unwrap(const zmq::message_t &zmsg){
    assert(zmsg.size());
    msgpack::sbuffer buffer;
    buffer.write(static_cast<const char*>(zmsg.data()), zmsg.size());
    std::memcpy(buffer.data(), zmsg.data(), zmsg.size());
    msgpack::unpacked msg;
    msgpack::unpack(&msg, buffer.data(), buffer.size());
    msgpack::object obj = msg.get();
    message result;
    obj.convert(&result);
    return result;
}

}
