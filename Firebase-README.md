### LibMiletus - Firebase interface module tutorial

If you want to use Firebase module interface, please read this
document to properly set your environment.

#### Create a Firebase account and project

In order to use arduino_firebase module, you need to have a Google account.
If you don't have it yet, please create it and access [Firebase Console](https://console.firebase.google.com).
You can create your project clicking on **"Add project"** button and choosing
the name and region which better suits your needs. When you are done, just
click on the **"Create Project""** and it is done! You have a Firebase project.

#### Download and include LibMiletus and Firebase libraries

Download [LibMiletus](https://github.com/marcosscarpim/LibMiletus) and
[Firebase-Arduino](https://github.com/marcosscarpim/firebase-arduino) forked
in my repository. It has same behavior from original libraries, but I need
to fix Firebase-Arduino conflicts to use it together with LibMiletus.

After downloading, include both libraries in your Arduino IDE. The simplest way
is going in **Sketch -> Include library -> Add .ZIP Library...**.

#### Get Firebase URL and database secret

In order to communicate with Firebase, you will need to save two informations from
Firebase Console:

1. **Database URL**:
it is found in the database tab. **Important:** save it without **http://** and the
**final slash**.
2. **Database secret**:
it is found in found in **Project Configuration -> Service Accounts -> Database Secret**.
Don't care about the deprecation message.

#### Run example code

Now you should be able to run the example code **Node-MCU-LED-Firebase.ino** found
in the examples folder. 

Please notice you need to update fields **WIFI_SSID** and **WIFI_PASSWORD** with your
Wifi information and **FIREBASE_HOST** and **FIREBASE_AUTH** with the database URL and
secret you saved from previous step respectively.
