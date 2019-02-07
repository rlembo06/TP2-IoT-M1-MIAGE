import device1 from "./device1.temperatures.mock";
import device2 from "./device2.temperatures.mock";
import device3 from "./device3.temperatures.mock";

let mock = device1.concat(device2, device3);

export default { documents: mock };
