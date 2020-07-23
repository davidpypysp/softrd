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

export const objectList = {
    state: initialState,
    reducers: {
        updateObjectValue: (
            state: ObjectListState,
            id: string,
            position: Vec3,
            rotation: Vec3
        ) =>
            produce(state, (draft) => {
                draft[id].position = position;
                draft[id].rotation = rotation;
            }),
        addObject: (state: ObjectListState, object: Object) =>
            produce(state, (draft) => {
                draft[object.id] = object;
            }),
        updateObjectPosition: (
            state: ObjectListState,
            id: string,
            position: Vec3
        ) =>
            produce(state, (draft) => {
                draft[id].position = position;
            }),
        updateObjectRotation: (
            state: ObjectListState,
            id: string,
            rotation: Vec3
        ) =>
            produce(state, (draft) => {
                draft[id].rotation = rotation;
            }),
    },
};
