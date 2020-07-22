import * as React from "react";
import { HTMLAttributes, shallow, ShallowWrapper } from "enzyme";
import { configure } from "enzyme";
import Adapter from "enzyme-adapter-react-16";
import { RowData } from "./ObjectBoard";

configure({ adapter: new Adapter() });

let child: ShallowWrapper<undefined, undefined> = null;

beforeEach(() => (child = shallow(<RowData title="abc" />)));

// checking that all is fine and component has been rendered
it("should render without error", () => expect(child.length).toBe(1));

it("should render one li component", () => {
    expect(child.find("li")).toHaveLength(1);
});
