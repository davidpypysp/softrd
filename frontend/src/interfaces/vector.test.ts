import { Vec3 } from "./vector";

test("Vec3 Test", () => {
    const v: Vec3 = { x: 1, y: 2, z: 3 };
    expect(v).toEqual({ x: 1.0, y: 2.0, z: 3.0 });
    expect(Object.keys(v).length).toBe(3);
});
