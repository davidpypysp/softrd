import React from "react";

export default class App extends React.Component {
  constructor(props) {
      super(props);
  }
  
  render() {
    console.log("render function");
    return (
        <span>Test span</span>
    );
  }
}
