import * as React from "react";
import { HTMLAttributes, shallow, ShallowWrapper } from "enzyme";
import { configure } from "enzyme";
import Adapter from "enzyme-adapter-react-16";
import { NumericInput } from "@blueprintjs/core";

import { Vec3Input } from "./VectorInput";

configure({ adapter: new Adapter() });

let child: ShallowWrapper<undefined, undefined> = null;
beforeEach(() => (child = shallow(<Vec3Input data={{ x: 1, y: 2, z: 3 }} />)));

// checking that all is fine and component has been rendered
it("should render without error", () => expect(child.length).toBe(1));

it("should render one Card component", () => {
    expect(child.find(NumericInput)).toHaveLength(3);
});
