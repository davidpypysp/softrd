import * as React from "react";
import { HTMLAttributes, shallow, ShallowWrapper } from "enzyme";
import { configure } from "enzyme";
import Adapter from "enzyme-adapter-react-16";
import { Tab, Tabs } from "@blueprintjs/core";
import RightPanel from "./RightPanel";
import ObjectBoard from "src/ui/Components/ObjectBoard";

configure({ adapter: new Adapter() });

let child: ShallowWrapper<undefined, undefined> = null;
beforeEach(() => (child = shallow(<RightPanel />)));

// checking that all is fine and component has been rendered
it("should render without error", () => expect(child.length).toBe(1));

it("should render one ObjectBoard component", () => {
    expect(child.find(Tab)).toHaveLength(1);
});
