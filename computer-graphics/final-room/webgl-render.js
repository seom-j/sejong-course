var light_x = 2.3,
    light_y = 3.0,
    light_z = 3.5;
var aspect = 0.0;
var u_AmbientLight, u_LightColor, u_LightPosition, u_color;
var modelMatrix, perspMatrix, viewMatrix, mvpMatrix, normalMatrix;

var currentColor = 0;
var colors = [
    new Float32Array([0.8, 0.3, 0.3, 1.0]), //red
    new Float32Array([0.3, 0.3, 0.8, 1.0]), // blue
    new Float32Array([0.8, 0.3, 0.8, 1.0]), // purple
    new Float32Array([0.3, 0.8, 0.8, 1.0]), // yellow
];


var blue = new Float32Array([0.3, 0.3, 0.8, 1.0]);
var red = new Float32Array([0.8, 0.3, 0.3, 1.0]);
var angle = 0;
var rotationDirection = -1;


function main() {
    var canvas = document.getElementById('webgl');

    var rotateClockwiseButton = document.getElementById('rotate-clockwise-button');
    var rotateCounterClockwiseButton = document.getElementById('rotate-counter-clockwise-button');
        rotateClockwiseButton.addEventListener('click', function() {
      rotationDirection = -1; // 시계 방향으로 1도씩 회전
    });
  
    rotateCounterClockwiseButton.addEventListener('click', function() {
        rotationDirection = 1; // 반시계 방향으로 1도씩 회전
    });


    var gl = getWebGLContext(canvas);
    if (!gl) {
        console.log('Failed to get the context');
        return;
    }

    aspect = canvas.width / canvas.height;
    var vShaderElement = document.getElementById("VertexShader");
    var fShaderElement = document.getElementById("FragmentShader");

    makeShaders(gl, vShaderElement, fShaderElement);

    var n = initVertexBuffers(gl);
    if (n < 0) {
        console.log('Failed to set verts');
        return;
    }

    modelMatrix = new Matrix4();
    perspMatrix = new Matrix4();
    viewMatrix = new Matrix4();
    mvpMatrix = new Matrix4();
    normalMatrix = new Matrix4();

    gl.enable(gl.DEPTH_TEST);

    u_LightColor = gl.getUniformLocation(gl.program, 'u_LightColor');
    u_LightPosition = gl.getUniformLocation(gl.program, 'u_LightPosition');
    u_AmbientLight = gl.getUniformLocation(gl.program, 'u_AmbientLight');
    u_color = gl.getUniformLocation(gl.program, 'u_color');


    gl.uniform3f(u_LightColor, 1.0, 1.0, 1.0);
    gl.uniform3f(u_AmbientLight, 0.25, 0.25, 0.25);
    gl.uniform4f(u_color, colors[0][0], colors[0][1], colors[0][2], colors[0][3]);
    draw(gl, n, u_LightPosition);
}


function makeShaders(context, vShaderElement, fShaderElement) {
    if (vShaderElement == null) {
        console.log("Failed to get the vert shader");
        return;
    }
    if (fShaderElement == null) {
        console.log("Failed to get the frag shader");
        return;
    }

    var vShaderSource = vShaderElement.firstChild.textContent;
    var fShaderSource = fShaderElement.firstChild.textContent;

    if (!initShaders(context, vShaderSource, fShaderSource)) {
        console.log('Failed to init shaders');
        return;
    }
}

function initVertexBuffers(gl) {
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3

    var vertices = new Float32Array([
        0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, // v0-v1-v2-v3 front
        0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, // v0-v3-v4-v5 right
        0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, // v0-v5-v6-v1 up
        -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, // v1-v6-v7-v2 left
        -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, // v7-v4-v3-v2 down
        0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5 // v4-v7-v6-v5 back
    ]);

    var normals = new Float32Array([
        0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // v0-v1-v2-v3 front
        1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, // v0-v3-v4-v5 right
        0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, // v0-v5-v6-v1 up
        -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, // v1-v6-v7-v2 left
        0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, // v7-v4-v3-v2 down
        0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0 // v4-v7-v6-v5 back
    ]);

    var indices = new Uint8Array([
        0, 1, 2, 0, 2, 3, // front
        4, 5, 6, 4, 6, 7, // right
        8, 9, 10, 8, 10, 11, // up
        12, 13, 14, 12, 14, 15, // left
        16, 17, 18, 16, 18, 19, // down
        20, 21, 22, 20, 22, 23 // back
    ]);

    // verts
    var vertsBuffer = gl.createBuffer();
    if (!vertsBuffer) {
        console.log('Faled to create verts buffer');
        return false;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, vertsBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    var a_position = gl.getAttribLocation(gl.program, 'a_position');
    if (a_position < 0) {
        console.log('Faled to get a_position location');
        return false;
    }
    gl.vertexAttribPointer(a_position, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_position);

    // normals
    var normalsBuffer = gl.createBuffer();
    if (!normalsBuffer) {
        console.log('Faled to create normals buffer');
        return false;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, normalsBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);

    var a_normal = gl.getAttribLocation(gl.program, 'a_normal');
    if (a_normal < 0) {
        console.log('Faled to get a_normal location');
        return false;
    }
    gl.vertexAttribPointer(a_normal, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(a_normal);

    var indexBuffer = gl.createBuffer();
    if (!indexBuffer) {
        console.log('Failed to create buffer');
        return false;
    }
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

    return indices.length;
}


function draw(context, n, u_LightPosition) {
    context.clearColor(0.0, 0.0, 0.0, 1.0);
    context.enable(context.DEPTH_TEST);

    context.uniform3f(u_LightPosition, light_x, light_y, light_z);

    var u_mMatrix = context.getUniformLocation(context.program, 'u_mMatrix');
    var u_mvpMatrix = context.getUniformLocation(context.program, 'u_mvpMatrix');
    var u_normalMatrix = context.getUniformLocation(context.program, 'u_normalMatrix');

    // model 
    angle += 1 * rotationDirection; // Increment the rotation angle
    modelMatrix.setRotate(angle, 0, 0, 1); // Apply rotation to model matrix (z-axis rotation)
    context.uniformMatrix4fv(u_mMatrix, false, modelMatrix.elements);
    

    // model view
    perspMatrix.setPerspective(30, aspect, 1, 100);
    viewMatrix.setLookAt(6, 6, 6, 0, 0, 0, 0, 1, 0);
    mvpMatrix.set(perspMatrix).multiply(viewMatrix).multiply(modelMatrix);
    context.uniformMatrix4fv(u_mvpMatrix, false, mvpMatrix.elements);

    // spesial for normals - detect invisible plates
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();
    context.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);

    context.clear(context.COLOR_BUFFER_BIT | context.DEPTH_BUFFER_BIT);
    context.drawElements(context.TRIANGLES, n, context.UNSIGNED_BYTE, 0); // center cube

    requestAnimationFrame(function () { draw(context, n, u_LightPosition); }); // Continue drawing with updated rotation angle
}


main();
