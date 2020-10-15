/*!
 * \authors
 * \version
 * \copyright
 * 
 * 
*/

#ifndef AbrisPlatform_h
#define AbrisPlatform_h

#include <ESP8266HTTPClient.h>
#include <stdint.h>
#include <ArduinoJson.h>

class AbrisPlatform {
	
	public:
	
		/*! Abrisplatform class constructor */
		AbrisPlatform();
		
		/*! Abrisplatform class constructor 
		\param[in] http
		*/
		AbrisPlatform(HTTPClient * http);
		
		/*! Abrisplatform class constructor 
		\param[in] http
		\param[in] addres
		*/
		AbrisPlatform(HTTPClient * http, const char * addres);
		
		 /*! Abrisplatform class destructor */
		~AbrisPlatform();
		
		/*! Abrisplatform class destructor */
		void setHTTPClient(HTTPClient * http);
		
		/*! Abrisplatform class destructor */
		void setHTTPAddres(const char * addres);
		
		/*! Abrisplatform class destructor */
		String authenticate(const char * login, const char * password);
		
		/*! Abrisplatform class destructor */
		String update(const char * schema , const char * table, const char * jsonFieldsValue, const String arrKey[], const char * jsonKeyValue);
		
		/*! Abrisplatform class destructor */
		String insert(const char * schema , const char * table, const char * jsonFieldsValue, const char * key);
		
		/*! Abrisplatform class destructor */
		bool getAuthenticateUser();
		
		int http_code; ///<
		
		
	private:
		
		HTTPClient * http = new HTTPClient(); ///<
		String login; ///<
        String password; ///<
		String addres; ///<
		String cookie; ///<
		bool authenticateUser = "false"; ///<
		
		const char * headerKeys[2] = {"Cookie", "Set-Cookie"}; ///<
        const size_t numberOfHeaders = 2; ///< 
		StaticJsonDocument<400> jsonDocument; ///<
		
		/*! Abrisplatform class destructor */
		void getCookie();
		

	
};
#endif