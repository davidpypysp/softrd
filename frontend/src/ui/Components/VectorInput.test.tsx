import * as React from "react";
import { HTMLAttributes, shallow, ShallowWrapper } from "enzyme";
import Header from "./Header";
import { configure } from "enzyme";
import Adapter from "enzyme-adapter-react-16";

import { Vec3Input } from "./Vec3Input";

configure({ adapter: new Adapter() });

let child: ShallowWrapper<undefined, undefined> = null;
beforeEach(() => (child = shallow(<Header />)));

// checking that all is fine and component has been rendered
it("should render without error", () => expect(child.length).toBe(1));

it("should render one Card component", () => {
    expect(child.find(Card)).toHaveLength(1);
}
