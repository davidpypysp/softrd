import { Vec3 } from "src/interfaces/vector";

export interface Object {
    id: string;
    name: string;
    position: Vec3;
    rotation: Vec3;
}
