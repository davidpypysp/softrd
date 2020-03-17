import { Object } from "src/interfaces/object";

interface ObjectListState { [id: string]: Object };

const initialState: ObjectListState = {
    "Camera": {
        name: "Camera",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "Box1": {
        name: "Box1",
        position: { x: 0, y: 0, z: 0 },
        rotation: { x: 1, y: 2, z: 3 },
    },
    "Box2": {
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
                [action.id]: {
                    name: action.name,
                    position: action.position,
                    rotation: action.rotation
                }
            };
        default:
            return state;
    }
};

export default objectListReducer;