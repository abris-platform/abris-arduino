#ifndef AbrisPlatform_h
#define AbrisPlatform_h

#include <ESP8266HTTPClient.h>
#include <stdint.h>
#include <ArduinoJson.h>

class AbrisPlatform {
	
	public:
		AbrisPlatform();
		AbrisPlatform(HTTPClient *);
		AbrisPlatform(HTTPClient *, const char * );
		
		~AbrisPlatform();
		
		
		void setHTTPClient(HTTPClient *);
		void setHTTPAddres(const char *);
		bool authenticate(const char * , const char * );
		
		String update(const char * , const char * , const char * , const String [], const char * );
		String insert(const char *, const char *, const char * , const char *);
		
		uint8_t http_code;
	
		
	private:
		String cookie;
		HTTPClient * http = new HTTPClient();
		String login;
        String password;
		String addres;
		const char * headerKeys[2] = {"Cookie", "Set-Cookie"};
        const size_t numberOfHeaders = 2;
		StaticJsonDocument<400> jsonDocument;
		
		void getCookie();
		
	
	
};
#endif