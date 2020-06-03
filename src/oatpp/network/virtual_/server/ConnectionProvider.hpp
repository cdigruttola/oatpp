/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_network_virtual__server_ConnectionProvider_hpp
#define oatpp_network_virtual__server_ConnectionProvider_hpp

#include "oatpp/network/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/Interface.hpp"

namespace oatpp { namespace network { namespace virtual_ { namespace server {

/**
 * Provider of "virtual" connections.
 * See &id:oatpp::network::virtual_::Interface;, &id:oatpp::network::virtual_::Socket; <br>
 * Extends &id:oatpp::network::ServerConnectionProvider;.
 */
class ConnectionProvider: public oatpp::network::ServerConnectionProvider {
private:
  std::shared_ptr<virtual_::Interface> m_interface;
  std::shared_ptr<virtual_::Interface::ListenerLock> m_listenerLock;
  bool m_open;
  v_io_size m_maxAvailableToRead;
  v_io_size m_maxAvailableToWrite;

public:
  /**
   * Constructor.
   * @param interface - &id:oatpp::network::virtual_::Interface;.
   */
  ConnectionProvider(const std::shared_ptr<virtual_::Interface>& interface);

  /**
   * Create shared ConnectionProvider.
   * @param interface - &id:oatpp::network::virtual_::Interface;.
   * @return - `std::shared_ptr` to ConnectionProvider.
   */
  static std::shared_ptr<ConnectionProvider> createShared(const std::shared_ptr<virtual_::Interface>& interface);

  /**
   * Limit the available amount of bytes to read from socket and limit the available amount of bytes to write to socket.
   * <br> This method is used for testing purposes only.<br>
   * @param maxToRead - maximum available amount of bytes to read.
   * @param maxToWrite - maximum available amount of bytes to write.
   */
  void setSocketMaxAvailableToReadWrtie(v_io_size maxToRead, v_io_size maxToWrite);

  /**
   * Break accepting loop.
   */
  void close() override;

  /**
   * Get incoming connection.
   * @return &id:oatpp::data::stream::IOStream;.
   */
  std::shared_ptr<IOStream> getConnection() override;

  /**
   * **NOT IMPLEMENTED!**<br>
   * No need to implement this.<br>
   * For Asynchronous IO in oatpp it is considered to be a good practice
   * to accept connections in a seperate thread with the blocking accept()
   * and then process connections in Asynchronous manner with non-blocking read/write.
   * <br>
   * *It may be implemented later.*
   */
  oatpp::async::CoroutineStarterForResult<const std::shared_ptr<oatpp::data::stream::IOStream>&> getConnectionAsync()
   override
  {
    /*
     *  No need to implement this.
     *  For Asynchronous IO in oatpp it is considered to be a good practice
     *  to accept connections in a seperate thread with the blocking accept()
     *  and then process connections in Asynchronous manner with non-blocking read/write
     *
     *  It may be implemented later
     */
    throw std::runtime_error(
     "[oatpp::network::virtual_::server::ConnectionProvider::getConnectionAsync()]: Error. Not implemented.");
  }

  /**
   * Does nothing.
   * @param connection
   */
  void invalidateConnection(const std::shared_ptr<IOStream>& connection) override
  {
    (void)connection;
    // DO Nothing.
  }
};

}}}}

#endif /* oatpp_network_virtual__server_ConnectionProvider_hpp */
