import * as React from "react";
import { HTMLAttributes, shallow, ShallowWrapper } from "enzyme";
import { configure } from "enzyme";
import Adapter from "enzyme-adapter-react-16";
import { Tab, Tabs } from "@blueprintjs/core";
import LeftPanel from "./LeftPanel";

configure({ adapter: new Adapter() });

let child: ShallowWrapper<undefined, undefined> = null;
beforeEach(() => (child = shallow(<LeftPanel />)));

// checking that all is fine and component has been rendered
it("should render without error", () => expect(child.length).toBe(1));

it("should render one Card component", () => {
    expect(child.find(Tab)).toHaveLength(3);
});
