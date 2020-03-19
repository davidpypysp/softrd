import { Object } from "src/interfaces/object";

export interface ObjectListState { [id: string]: Object };

const initialState: ObjectListState = {
    "camera": {
        id: "camera",
        name: "Camera",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "box1": {
        id: "box1",
        name: "Box1",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "box2": {
        id: "box2",
        name: "Box2",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    }
};

const objectListReducer = (state: ObjectListState = initialState, action) => {
    switch (action.type) {
        case 'UPDATE_OBJECT_VALUE':
            return {
                ...state,
                [action.id]: {
                    postion: action.position,
                    rotation: action.rotation
                }
            };
        case 'ADD_OBJECT':
            return {
                ...state,
                [action.object.id]: action.object
            };
        default:
            return state;
    }
};

export default objectListReducer;