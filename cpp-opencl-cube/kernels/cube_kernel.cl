__kernel void cube_kernel(__global float4* vertices, float angleX, float angleY, float angleZ) {
    int id = get_global_id(0);
    
    // Define rotation matrices
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);

    // Original vertex position
    float4 v = vertices[id];

    // Rotate around X
    float y = v.y * cosX - v.z * sinX;
    float z = v.y * sinX + v.z * cosX;
    v.y = y;
    v.z = z;

    // Rotate around Y
    float x = v.x * cosY + v.z * sinY;
    z = -v.x * sinY + v.z * cosY;
    v.x = x;
    v.z = z;

    // Rotate around Z
    x = v.x * cosZ - v.y * sinZ;
    y = v.x * sinZ + v.y * cosZ;
    v.x = x;
    v.y = y;

    // Write back the transformed vertex
    vertices[id] = v;
}