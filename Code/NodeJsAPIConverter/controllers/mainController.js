import mqtt from "mqtt"
const clientId = "Yaman's Server";
const connectUrl = "mqtt://mqtt.cetools.org:1884";
import cache from "memory-cache";

const MQTT_USER_NAME = 'NAME';
const MQTT_PASSWORD = 'PASSWORD';

export default class mainController {
  constructor() {
  }

 async realMQTT(req, res) {
    try{
      
      

      const client = mqtt.connect(connectUrl, {
        clientId,
        clean: true,
        connectTimeout: 4000,
        username: MQTT_USER_NAME,
        password: MQTT_PASSWORD,
        reconnectPeriod: 1000,
      })

      var index = cache.get('fake-index')
      if(index === null)
      {
        index = 0;
        cache.put('fake-index', '0');
      } 
      client.publish('student/CASA0022/whatscup/fake/currentMatch', '')
      
      //moving to the next fake item
      if(index === 4)
      {
        cache.put('fake-index', '0');
      } else { 
        cache.put('fake-index', parseInt(index) + 1);
      }

      res.send("Success");
    } catch (err) {
      console.log(err);
      res.sendStatus(500);
    }
  }
}