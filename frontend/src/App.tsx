import { Slider, Switch, Form } from "antd";
import React, { useState, useEffect } from "react";
import "antd/dist/antd.css";
import { SliderValue } from "antd/lib/slider";
import { updateRGB, updateCycle, updateLED, getStatus } from "./api";
import "./App.css";

function App() {
  const [rgb, setRGB] = useState({ red: 0, green: 0, blue: 0 });
  const [led, setLed] = useState(false);
  const [cycle, setCycle] = useState(false);
  const [screenHeight, setScreenHeight] = useState(window.innerHeight);

  useEffect(() => {
    getStatus().then((status) => {
      setRGB({ red: status.red, green: status.green, blue: status.blue });
      setCycle(status.cycle);
      setLed(status.led);
    });
  }, []);

  useEffect(() => {
    function onResize() {
      console.log("Screen size changed");
      setScreenHeight(window.innerHeight);
    }
    window.onresize = onResize;
    return function cancel() {
      window.onresize = null;
    };
  });

  function onAfterRedChange(value: SliderValue) {
    if (value !== rgb.red) {
      const newRgb = { ...rgb, red: value as number };
      setRGB(newRgb);
      updateRGB(newRgb);
    }
  }
  function onAfterGreenChange(value: SliderValue) {
    if (value !== rgb.green) {
      const newRgb = { ...rgb, green: value as number };
      setRGB(newRgb);
      updateRGB(newRgb);
    }
  }
  function onAfterBlueChange(value: SliderValue) {
    if (value !== rgb.blue) {
      const newRgb = { ...rgb, blue: value as number };
      setRGB(newRgb);
      updateRGB(newRgb);
    }
  }

  function onCycle(checked: boolean) {
    setCycle(checked);
    updateCycle(checked);
  }

  function onLED(checked: boolean) {
    setLed(checked);
    updateLED(checked);
  }

  return (
    <div className="site-content" style={{ height: screenHeight }}>
      <div
        style={{
          display: "flex",
          flexDirection: "row",
          justifyContent: "space-around",
        }}
      >
        <Form.Item label="Cycle:">
          <Switch onChange={onCycle} checked={cycle} />
        </Form.Item>
        <Form.Item label="LED:">
          <Switch onChange={onLED} checked={led} />
        </Form.Item>
      </div>
      <div
        style={{
          paddingTop: 50,
          paddingBottom: 100,
          flex: 1,
          display: "flex",
          flexDirection: "row",
          justifyContent: "space-around",
        }}
      >
        <div>
          <Slider
            className="red-slider"
            onChange={onAfterRedChange}
            vertical
            value={rgb.red}
            defaultValue={0}
            max={255}
          />
        </div>
        <div>
          <Slider
            className="green-slider"
            onChange={onAfterGreenChange}
            vertical
            value={rgb.green}
            defaultValue={0}
            max={255}
          />
        </div>
        <div>
          <Slider
            className="blue-slider"
            onChange={onAfterBlueChange}
            vertical
            value={rgb.blue}
            defaultValue={0}
            max={255}
          />
        </div>
      </div>
    </div>
  );
}

export default App;
