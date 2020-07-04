import { Object } from "src/interfaces/object";
import { Vec3 } from "src/interfaces/vector";

export const addObject = (object: Object) => ({
    type: "ADD_OBJECT",
    object,
});

export const updateObjectPosition = (id: string, position: Vec3) => ({
    type: "UPDATE_OBJECT_POSITION",
    id,
    position,
});

export const updateObjectRotation = (id: string, rotation: Vec3) => ({
    type: "UPDATE_OBJECT_ROTATION",
    id,
    rotation,
});
