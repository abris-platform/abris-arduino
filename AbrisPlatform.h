/*!
 * \authors Pchelincev Ivan
 * \version 0.0.1
 * \copyright
 * \brief Arduino Library for Abrisplatform (https://abrisplatform.com)
 * 
*/

#ifndef AbrisPlatform_h
#define AbrisPlatform_h

#include <ESP8266HTTPClient.h>
#include <stdint.h>
#include <ArduinoJson.h>


class AbrisPlatform {
	public:
		/*! 
		 * Abrisplatform class constructor 
		*/
		AbrisPlatform();
		
		/*! 
		 * Abrisplatform class constructor 
		 * \param[in] http HTTPClient object address
		*/
		AbrisPlatform(HTTPClient * http);
		
		/*! 
		 * Abrisplatform class constructor 
		 * \param[in] http HTTPClient object address
		 * \param[in] address Server address
		*/
		AbrisPlatform(HTTPClient * http, const char * address);
		
		 /*! Abrisplatform class destructor */
		~AbrisPlatform();
		
		/*!
		 * Set the address HTTPClient object
		 * \param[in] http HTTPClient object address
		*/
		void setHTTPClient(HTTPClient * http);
		
		/*! 
		 * Abrisplatform class destructor 
		 * \param[in] address Server address
		*/
		void setHTTPAddress(const char * address);
		
		/*! Authenticate - database connection
		 * \param[in] login Database login
		 * \param[in] password Database password
		 * \return Server response
		*/
		String authenticate(const char * login, const char * password);
		
		/*! Update - update rows of a table
		 * \param[in] schema Database schema name
		 * \param[in] table Database table name
		 * \param[in] jsonFieldsValue  Json update data(column:value)
		 * \param[in] jsonKeyValue Values of "WHERE" condition column in json format (column:value or column:[value1,value2])
		 * \return Server response
		*/
		String update(const char * schema, const char * table, const char * jsonFieldsValue, const char * jsonKeyValue);
		
		/*! Authenticate - database connection
		 * \param[in] schema Database schema name
		 * \param[in] table Database table name
		 * \param[in] json Data (column:value)
		 * \param[in] key Primary key column
		 * \return Server response
		*/
		String insert(const char * schema, const char * table, const char * jsonFieldsValue, const char * key);
		
		/*! Get database connection flag */
		bool getAuthenticateUser();
		
		int http_code; ///< Server response code
		
		
	private:	
		HTTPClient * http = new HTTPClient(); ///< HTTPClient object address
		String login; ///< Database login
		String password; ///< Database password
		String address; ///< Server address
		String cookie; ///< Cookie data
		bool authenticateUser = false; ///< Database connection flag
		
		const char * headerKeys[2] = { "Cookie", "Set-Cookie" }; ///< Key array for POST request header
        const size_t numberOfHeaders = 2; ///< Number of keys for POST request header
		StaticJsonDocument<400> jsonDocument; ///< StaticJsonDocument class object
		
		/*! Сookie data from server */
		void getCookie();
};
#endif