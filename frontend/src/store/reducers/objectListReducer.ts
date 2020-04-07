import { Object } from "src/interfaces/object";

export interface ObjectListState { [id: string]: Object };

const initialState: ObjectListState = {
    "box0": {
        id: "box0",
        name: "box0",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "box1": {
        id: "box1",
        name: "Box1",
        position: { x: 2, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "box2": {
        id: "box2",
        name: "Box2",
        position: { x: 0, y: 0, z: 2 },
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
        case 'UPDATE_OBJECT_POSITION':
            return {
                ...state,
                [action.id]: {
                    ...state[action.id],
                    position: action.position,
                }
            };
        case 'UPDATE_OBJECT_ROTATION':
            return {
                ...state,
                [action.id]: {
                    ...state[action.id],
                    rotation: action.rotation,
                }
            };
        default:
            return state;
    }
};

export default objectListReducer;