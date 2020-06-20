import _ from "lodash";

async function _updateRGB(rgb: { red: number; green: number; blue: number }) {
  await fetch("http://moonlamp.local/rgb", {
    method: "PUT",
    headers: {
      "content-type": "application/json",
    },
    body: JSON.stringify({
      red: rgb.red,
      green: rgb.green,
      blue: rgb.blue,
    }),
  });
}

const updateRGB = _.throttle(_updateRGB, 200);

async function updateCycle(on: boolean) {
  await fetch("http://moonlamp.local/cycle", {
    method: "PUT",
    headers: {
      "content-type": "application/json",
    },
    body: JSON.stringify({
      on,
    }),
  });
}

async function updateLED(on: boolean) {
  await fetch("http://moonlamp.local/led", {
    method: "PUT",
    headers: {
      "content-type": "application/json",
    },
    body: JSON.stringify({
      on,
    }),
  });
}

async function getStatus(): Promise<{
  red: number;
  green: number;
  blue: number;
  cycle: boolean;
  led: boolean;
}> {
  const response = await fetch("http://moonlamp.local/status");
  const json = await response.json();
  return json;
}

export { updateRGB, updateCycle, updateLED, getStatus };
