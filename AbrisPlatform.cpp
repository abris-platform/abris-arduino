#include <AbrisPlatform.h>

AbrisPlatform::AbrisPlatform(){
	
};

AbrisPlatform::AbrisPlatform(HTTPClient * http){
	this->http = http;
};

AbrisPlatform::AbrisPlatform(HTTPClient * http, const char * addres){
	this->http = http;
	this->addres = "http://"+ String(addres) + "/Server/request.php";
};
		
AbrisPlatform::~AbrisPlatform(){
	delete  http;
};
		
		
void AbrisPlatform::setHTTPClient(HTTPClient * http){
	this->http = http;
	
};

void AbrisPlatform::setHTTPAddres(const char * addres){
	this->addres = "http://" + String(addres) + "/Server/request.php";;
};

void AbrisPlatform::getCookie(){
	String request;
	request = "method=get_current_language&client_version=Dev&params=[{}]";
	http->begin(this->addres);
	http->addHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");	
	http->collectHeaders(this->headerKeys, this->numberOfHeaders);
	http->setTimeout(3000);
	this->http_code = http->POST(request);
	this->cookie = http->header(1);
	this->cookie = this->cookie.substring(0,this->cookie.indexOf(";"));     
};


String AbrisPlatform::authenticate(const char * login, const char * password){
	this->getCookie();
	String request;      
	request = "method=authenticate&";
	request += "params=[{\"usename\":\""+String(login)+"\",\"passwd\":\""+String(password)+"\"}]";
	http->addHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
	http->addHeader("Cookie",  this->cookie);
	this->http_code = http->POST(request); 
	
	jsonDocument.clear();
	deserializeJson(jsonDocument, http->getString());
	
	if((jsonDocument["result"][0]["usename"] == login) && !jsonDocument["error"]){
		this->login = login;
		this->password = password;
		this->authenticateUser = true;
	}
	else{
		this->authenticateUser = false;
	}
	
	return  http->getString();

	
};

String AbrisPlatform::update(const char * schema , const char * table, const char * jsonFieldsValue, const char * jsonKeyValue){
	
	if(!this->authenticateUser) return "error authenticate";
	
	String request;
    request = "method=updateEntity&";
	request += "params=[{";
	request += "\"entityName\":\""+String(table)+"\",";
	request += "\"schemaName\":\""+String(schema)+"\",";
	jsonDocument.clear();
	deserializeJson(jsonDocument, jsonKeyValue);
	String requestKeys = "[";
	String valueKeys = "[";
	String valueKey = "";
		
	
	JsonObject root = jsonDocument.as<JsonObject>();
	String rrrr;
	for(JsonPair kv:root) {	
		serializeJson(kv.value(), valueKey);
		valueKeys += ""+ valueKey +",";
		requestKeys += "\""+ String(kv.key().c_str()) + "\",";
		valueKey = "";	
	}
	
	valueKeys = valueKeys.substring(0,valueKeys.length()-1);
	requestKeys =requestKeys.substring(0,requestKeys.length()-1);
	
	requestKeys += "]";
    valueKeys += "]";
	
	request += "\"key\":"+requestKeys+",";
	request += "\"value\":"+valueKeys+",";
	request += "\"fields\":"+ String(jsonFieldsValue) +",";
	request += "\"files\":[],";
	request += "\"types\":null";
	request += "}]";
	
	http->addHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    http->addHeader("Cookie",  this->cookie);
    http->setTimeout(3000);
    this->http_code = http->POST(request);
	
	return http->getString();
	
   
};

String AbrisPlatform::insert(const char * schema , const char * table, const char * jsonFieldsValue, const char * key){
	
	if(!this->authenticateUser) return "error authenticate";
	
	String request;
    request = "method=addEntities&";
	request += "params=[{";
	request += "\"entityName\":\""+String(table)+"\",";
	request += "\"schemaName\":\""+String(schema)+"\",";
	request += "\"fields\":["+ String(jsonFieldsValue) +"],";
	request += "\"files\":[],";
	request += "\"key\":\""+ String(key)+"\",";
	request += "\"types\":null";
	request += "}]";
	
    http->addHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    http->addHeader("Cookie",  this->cookie);
    http->setTimeout(3000);
    this->http_code = http->POST(request);
   
	return http->getString();
};

bool AbrisPlatform::getAuthenticateUser(){
	return this->authenticateUser;
}






