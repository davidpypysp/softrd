import React from "react";
import { Card } from "@blueprintjs/core";

import { createUseStyles } from 'react-jss';

const useStyles = createUseStyles({
    header: {
        height: 35,
        padding: 5,
    },
});

export default function Header(props) {
    const classes = useStyles();
    return <Card className={classes.header}>Help</Card>;
}
