import { createAction, createReducer } from "@reduxjs/toolkit";

import { Object } from "src/interfaces/object";
import { Vec3 } from "src/interfaces/vector";
import produce from "immer";

export interface ObjectListState {
    [id: string]: Object;
}

const initialState: ObjectListState = {
    box0: {
        id: "box0",
        name: "box0",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    // box1: {
    //     id: "box1",
    //     name: "Box1",
    //     position: { x: 2, y: 0, z: 0 },
    //     rotation: { x: 1, y: 2, z: 3 },
    // },
    // box2: {
    //     id: "box2",
    //     name: "Box2",
    //     position: { x: 0, y: 0, z: 2 },
    //     rotation: { x: 1, y: 2, z: 3 },
    // },
};

export const updateObjectValue = createAction(
    "UPDATE_OBJECT_VALUE",
    (id: string, position: Vec3, rotation: Vec3) => ({
        payload: {
            id,
            position,
            rotation,
        },
    })
);

export const addObject = createAction("ADD_OBJECT", (object: Object) => ({
    payload: object,
}));

export const updateObjectPosition = createAction(
    "UPDATE_OBJECT_POSITION",
    (id: string, position: Vec3) => ({
        payload: {
            id,
            position,
        },
    })
);

export const updateObjectRotation = createAction(
    "UPDATE_OBJECT_ROTATION",
    (id: string, rotation: Vec3) => ({
        payload: {
            id,
            rotation,
        },
    })
);

export const objectListReducer = createReducer(initialState, (builder) =>
    builder
        .addCase(updateObjectValue, (state, action) => {
            const { id, position, rotation } = action.payload;
            state[id].position = position;
            state[id].rotation = rotation;
        })
        .addCase(addObject, (state, action) => {
            state[action.payload.id] = action.payload;
        })
        .addCase(updateObjectPosition, (state, action) => {
            const { id, position } = action.payload;
            state[id].position = position;
        })
        .addCase(updateObjectRotation, (state, action) => {
            console.info("updateObjectRotation", action);
            const { id, rotation } = action.payload;
            state[id].rotation = rotation;
        })
);
