/*
 * =====================================================================================
 *
 *       Filename:  adafruit_sensor.cc
 *
 *    Description:  Wrapper for the Adafruit Unified Sensor Driver in Node.js
 *                  (https://github.com/adafruit/Adafruit_Sensor)
 *
 *        Version:  1.0
 *        Created:  11/02/2014 19:42:44
 *       Revision:  none
 *
 *         Author:  Ben Peters (bencpeters@gmail.com)
 *
 * =====================================================================================
 */

#include <node.h>
#include <v8.h>

#include "Adafruit_Sensor.h"

using namespace v8;

Handle<Value> ParseSensorEventT(const Arguments& args) {
  HandleScope scope;
  union {
    sensors_event_t event;
    uint8_t binary [sizeof(sensors_event_t)];
  } raw_data;
  Local<Array> arr_data;
  Local<String> string_data;
  Local<String> sensor_type;
  Local<Object> data_obj;
  
  if (args[0]->IsString()) {
    string_data = args[0]->ToString();
    string_data->WriteUtf8((char *) &raw_data.binary, sizeof(sensors_event_t));
  } else if (args[0]->IsArray()) {
    arr_data = Local<Array>::Cast(args[0]->ToObject());
    if (arr_data->Length() != sizeof(sensors_event_t)) {
      return scope.Close(Null());
    }
    for (uint32_t i = 0; i < arr_data->Length(); ++i) {
      raw_data.binary[i] = (uint8_t) arr_data->Get(i)->Uint32Value();
    }
  } else {
    return scope.Close(Null());
  }

  Local<Object> obj = Object::New();

  obj->Set(String::NewSymbol("version"), Integer::New(raw_data.event.version));
  obj->Set(String::NewSymbol("sensorId"), Integer::New(raw_data.event.sensor_id));

  switch (raw_data.event.type) {
    case SENSOR_TYPE_ACCELEROMETER:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("accelerometer"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("x"), Number::New((double) raw_data.event.acceleration.x));
      data_obj->Set(String::NewSymbol("y"), Number::New((double) raw_data.event.acceleration.y));
      data_obj->Set(String::NewSymbol("z"), Number::New((double) raw_data.event.acceleration.z));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.acceleration.status, 1));
      obj->Set(String::NewSymbol("acceleration"), data_obj);
      break;
    case SENSOR_TYPE_MAGNETIC_FIELD:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("magnetic_field"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("x"), Number::New((double) raw_data.event.magnetic.x));
      data_obj->Set(String::NewSymbol("y"), Number::New((double) raw_data.event.magnetic.y));
      data_obj->Set(String::NewSymbol("z"), Number::New((double) raw_data.event.magnetic.z));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.magnetic.status, 1));
      obj->Set(String::NewSymbol("magnetic"), data_obj);
      break;
    case SENSOR_TYPE_ORIENTATION:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("orientation"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("roll"), Number::New((double) raw_data.event.orientation.roll));
      data_obj->Set(String::NewSymbol("pitch"), Number::New((double) raw_data.event.orientation.pitch));
      data_obj->Set(String::NewSymbol("heading"), Number::New((double) raw_data.event.orientation.heading));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.orientation.status, 1));
      obj->Set(String::NewSymbol("orientation"), data_obj);
      break;
    case SENSOR_TYPE_GYROSCOPE:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("gyroscope"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("x"), Number::New((double) raw_data.event.gyro.x));
      data_obj->Set(String::NewSymbol("y"), Number::New((double) raw_data.event.gyro.y));
      data_obj->Set(String::NewSymbol("z"), Number::New((double) raw_data.event.gyro.z));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.gyro.status, 1));
      obj->Set(String::NewSymbol("gyro"), data_obj);
      break;
    case SENSOR_TYPE_LIGHT:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("light"));
      obj->Set(String::NewSymbol("light"), Number::New((double) raw_data.event.light));
      break;
    case SENSOR_TYPE_PRESSURE:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("pressure"));
      obj->Set(String::NewSymbol("pressure"), Number::New((double) raw_data.event.pressure));
      break;
    case SENSOR_TYPE_PROXIMITY:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("proximity"));
      obj->Set(String::NewSymbol("distance"), Number::New((double) raw_data.event.distance));
      break;
    case SENSOR_TYPE_GRAVITY:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("gravity"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("x"), Number::New((double) raw_data.event.acceleration.x));
      data_obj->Set(String::NewSymbol("y"), Number::New((double) raw_data.event.acceleration.y));
      data_obj->Set(String::NewSymbol("z"), Number::New((double) raw_data.event.acceleration.z));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.acceleration.status, 1));
      obj->Set(String::NewSymbol("acceleration"), data_obj);
      break;
    case SENSOR_TYPE_LINEAR_ACCELERATION:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("linear_acceleration"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("x"), Number::New((double) raw_data.event.acceleration.x));
      data_obj->Set(String::NewSymbol("y"), Number::New((double) raw_data.event.acceleration.y));
      data_obj->Set(String::NewSymbol("z"), Number::New((double) raw_data.event.acceleration.z));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.acceleration.status, 1));
      obj->Set(String::NewSymbol("acceleration"), data_obj);
      break;
    case SENSOR_TYPE_ROTATION_VECTOR:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("rotation_vector"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("roll"), Number::New((double) raw_data.event.orientation.roll));
      data_obj->Set(String::NewSymbol("pitch"), Number::New((double) raw_data.event.orientation.pitch));
      data_obj->Set(String::NewSymbol("heading"), Number::New((double) raw_data.event.orientation.heading));
      data_obj->Set(String::NewSymbol("status"), String::NewSymbol((char *) &raw_data.event.orientation.status, 1));
      obj->Set(String::NewSymbol("orientation"), data_obj);
      break;
    case SENSOR_TYPE_RELATIVE_HUMIDITY:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("relative_humidity"));
      obj->Set(String::NewSymbol("relative_humidity"), Number::New((double) raw_data.event.relative_humidity));
      break;
    case SENSOR_TYPE_AMBIENT_TEMPERATURE:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("ambient_temperature"));
      obj->Set(String::NewSymbol("temperature"), Number::New((double) raw_data.event.temperature));
      break;
    case SENSOR_TYPE_VOLTAGE:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("voltage"));
      obj->Set(String::NewSymbol("voltage"), Number::New((double) raw_data.event.voltage));
      break;
    case SENSOR_TYPE_CURRENT:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("current"));
      obj->Set(String::NewSymbol("current"), Number::New((double) raw_data.event.current));
      break;
    case SENSOR_TYPE_COLOR:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("color"));
      data_obj = Object::New();
      data_obj->Set(String::NewSymbol("r"), Number::New((double) raw_data.event.color.r));
      data_obj->Set(String::NewSymbol("g"), Number::New((double) raw_data.event.color.g));
      data_obj->Set(String::NewSymbol("b"), Number::New((double) raw_data.event.color.b));
      data_obj->Set(String::NewSymbol("rgba"), Integer::New(raw_data.event.color.rgba));
      obj->Set(String::NewSymbol("color"), data_obj);
      break;
    default:
      obj->Set(String::NewSymbol("type"), String::NewSymbol("unknown"));
      break;
  };
  obj->Set(String::NewSymbol("timestamp"), Integer::New(raw_data.event.timestamp));

  return scope.Close(obj);
};

#if 0
Handle<Value> CreateAdafruitSensor(const Arguments& args) {
  HandleScope scope;
  sensor_t sensor;
  Local<String> name;
  int32_t int_val;
  float float_val;

  name = args[0]->ToString();
  name->WriteAscii(&sensor.name, name->Length > 12 ? 12 : name->Length);

  sensor.version = args[1]->ToInt32()->Value();
  sensor.sensor_id = args[2]->ToInt32()->Value();
  sensor.type = args[3]->ToInt32()->Value();
  sensor.max_value = (float) args[4]->ToNumber()->Value();
  sensor.min_value = (float) args[5]->ToNumber()->Value();
  sensor.resolution = (float) args[6]->ToNumber()->Value();
  sensor.min_delay = args[7]->ToInt32()->Value();

  Local<Object> obj = Object::New();

};
#endif

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("getEvent"), FunctionTemplate::New(ParseSensorEventT)->GetFunction());
};

NODE_MODULE(adafruit_sensor, init)
