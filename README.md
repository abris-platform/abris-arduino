# Arduino Library for Abrisplatform
(https://abrisplatform.com)


## Installation procedure

### Setting arduino for the esp8266 firmware
> https://www.arduino.cc/en/Guide/Libraries

### Installing additional arduino libraries
> https://www.arduino.cc/en/Guide/Libraries

### Library connection : ESP8266HTTPClient, ArduinoJson, ESP8266WiFi.

> https://github.com/esp8266/Arduino

> https://github.com/bblanchon/ArduinoJson

> https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html


## Description

### SetHTTPClient

Set the address HTTPClient object.
```c++
void setHTTPClient(HTTPClient *http);
```
#### Params:
- `http` - HTTPClient object address.
#### Example:
```c++
HTTPClient http;
abrisplatform.setHTTPClient(&http);
```

**Important** - the method is called before `authenticate`.


### SetHTTPAddress

Set the server address
```c++
void setHTTPAddress(const char * address);
```
#### Params:
- `address` - server address.
#### Example:
```c++
abrisplatform.setHTTPAddress("localhost");
```

**Important** - the method is called before `authenticate`.


### Authenticate

#### Authenticate - database connection.
```c++
void authenticate(const char * login, const char * password);
```
#### Params:
- `login` - database login, 
- `password` - database password.
#### Example:
```c++
abrisplatform.authenticate("username", "password");
```


### Insert

#### Insert - create new rows in a table.
```c++
String insert(const char * schema , const char * table, const char * jsonFieldsValue, const char * key);
```
#### Params:
- `schema` -  database schema name,
- `table` -  database table name,
- `jsonFieldsValue` - json data ( column  : value ),
- `key` - primary key column.
#### Example:
```c++
abrisplatform.insert("public", "sensor", {"field1":"value1", "field2":"value2"}, "sensor_key");
```
#### SQL: 
```sql
INSERT INTO public.sensor(field1,field2) VALUE ('value1','value2');
```


### Update

#### Update - update rows of a table.
```c++
String update(const char * schema, const char * table, const char * jsonFieldsValue, const char * jsonKeyValue);
```
#### Params:
- `schema` -  database schema name,
- `table` -  database table name,
- `jsonFieldsValue` - json update data( column  : value ),
- `jsonKeyValue` -  values of "WHERE" condition column in json format ( column : value or column : [value1, value2]).
#### Example:
```c++
abrisplatform.update("public", "sensor", { "field1":"value1", "field2":"value2" }, { "fieldKey1":["1", "2"], "fieldKey2":["11", "12"] });
```
#### SQL:
```sql
UPDATE public.sensor SET field1='value1', field2='value2' WHERE fieldKey1 = '1' AND fieldKey2 = '11';
```

```sql
UPDATE public.sensor SET field1='value1', field2='value2' WHERE fieldKey1 = '2' AND fieldKey2 = '12';
```