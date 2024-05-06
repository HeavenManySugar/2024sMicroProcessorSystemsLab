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

function controlLED(LED, POWER) {
  let child_process = require("child_process");
  let process = child_process.execFile("sudo", ["./C++/gpio", LED, POWER]);
  process.stdout.on("data", function (data) {
    console.log(data);
  });
  process.stderr.on("data", function (data) {
    console.log(data);
  });
}

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
