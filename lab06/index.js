const { profileEnd } = require("console");
const express = require("express");
const app = express();
const port = 8080;

app.get("/", (req, res) => {
  console.log(req.query);
  if (req.query.status) {
    console.log("LED Status: " + req.query.status);
    if (req.query.led1) {
      controlLED("LED1", req.query.status);
    }
    if (req.query.led2) {
      controlLED("LED2", req.query.status);
    }
    if (req.query.led3) {
      controlLED("LED3", req.query.status);
    }
    if (req.query.led4) {
      controlLED("LED4", req.query.status);
    }
  } else {
    console.log("Mode_Shine: " + req.query.frequency);
    if (req.query.frequency) {
      controlLED("Mode_Shine", req.query.frequency);
    }
  }
  res.sendFile(__dirname + "/index.html");
});

app.get('/readadc', (req, res) =>{
  test().then((value) => {
    console.log(parseInt(value));
    res.write(`${value}`)
    res.end()
  })
})

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function Mode_Shine(frequency) {
  for (let i = 0; i < frequency; i++) {
    let value2 = await readadc().then((value) => {
      return parseInt(value);
    })
    console.log(value2)
    controlLED("LED1", "on");
    controlLED("LED2", "on");
    controlLED("LED3", "off");
    controlLED("LED4", "off");
    await sleep(500+value2*10);
    controlLED("LED1", "off");
    controlLED("LED2", "off");
    controlLED("LED3", "on");
    controlLED("LED4", "on");
    await sleep(500+value2*10);
  }
  console.log('Done');
  controlLED("LED1", "off");
  controlLED("LED2", "off");
  controlLED("LED3", "off");
  controlLED("LED4", "off");
}


function controlLED(LED, POWER) {
  let child_process = require("child_process");
  if(LED === "Mode_Shine"){
    console.log(POWER);
    Mode_Shine(POWER);
    return;
  }
  let process = child_process.execFile("sudo", ["./C++/main", LED, POWER]);
  process.stdout.on("data", function (data) {
    console.log(data);
  });
  process.stderr.on("data", function (data) {
    console.log(data);
  });
}

function test() {
  return new Promise(function(resolve, reject) {
    let child_process = require("child_process");
    let process = child_process.spawn('python' , ["./python/test.py"]);

    process.stdout.on('data', (data)=>{
      resolve(`${data}`);
    });

    process.stderr.on('data', (data)=>{
      reject(data);
    })
  })
}

function readadc() {
  return new Promise(function(resolve, reject) {
    let child_process = require("child_process");
    let process = child_process.spawn('python' , ["./python/readadc.py"]);

    process.stdout.on('data', (data)=>{
      resolve(`${data}`);
    });

    process.stderr.on('data', (data)=>{
      reject(data);
    })
  })
}


app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
