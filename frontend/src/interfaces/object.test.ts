import { Object } from "./object";
import { Vec3 } from "./vector";

test("Object Test", () => {
    const position: Vec3 = { x: 1, y: 2, z: 3 };
    const rotation: Vec3 = { x: 0.1, y: 0.1, z: 0.1 };
    const sceneObject: Object = {
        id: "abcd",
        name: "scene_obj",
        position: position,
        rotation: rotation,
    };
    expect(Object.keys(sceneObject).length).toBe(4);
    expect(sceneObject).toHaveProperty("name", "scene_obj");
    expect(sceneObject).toHaveProperty("id");
});
