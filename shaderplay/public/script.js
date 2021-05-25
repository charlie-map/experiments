const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const BasicShader = {

	uniforms: { },

	vertexShader: /* glsl */`
		varying vec3 fNormal;
		varying vec3 fPosition;
		varying float intensity;

		const vec3 light = vec3(1.0, 1.0, 1.0);
		const vec3 ambient = vec3(0.01, 0.01, 0.01);

		void main() {
			fNormal = normalize(normalMatrix * normal);
  			vec4 pos = modelViewMatrix * vec4(position, 1.0);
  			fPosition = pos.xyz;
  
  			vec3 view = normalize(projectionMatrix * vec4(0.0, 0.0, 0.0, 1.0) - vec4(fPosition, 1.0)).xyz;
  			vec3 lightDir = normalize(light - fPosition);
  			float diffuse = dot(lightDir, fNormal);
  			intensity = diffuse + dot(diffuse * 2.0 * fNormal - lightDir, view);

  			if (intensity < 0.0) {
    			intensity = 0.0;
  			}
  
  			gl_Position = projectionMatrix *pos;		
  		}`,

	fragmentShader: /* glsl */`
		varying float intensity;

		void main() {
  			gl_FragColor = vec4(1.0, 0.69, 0.4, 1.0) * (intensity + 0.1);
		}`

};

// const gl = renderer.getContext();

// const glVertexShader = renderer.WebGLShader( gl, gl.VERTEX_SHADER, BasicShader.vertexShader );
// const glFragmentShader = renderer.WebGLShader( gl, gl.FRAGMENT_SHADER, BasicShader.fragmentShader );

// const program = gl.createProgram();

// gl.attachShader( program, glVertexShader );
// gl.attachShader( program, glFragmentShader );

// gl.linkProgram( program );

let shaderMaterial = new THREE.ShaderMaterial({
  vertexShader:   BasicShader.vertexShader,
  fragmentShader: BasicShader.fragmentShader
});

const loader = new THREE.GLTFLoader();
let car;

loader.load('scene.gltf', function (gltf) {
	car = new THREE.Mesh( gltf, shaderMaterial );
	scene.add( car );
}, undefined, function (error) {
	console.error(error);
});

// const geometry = new THREE.BoxGeometry();
// const cube = new THREE.Mesh( geometry, shaderMaterial );
// scene.add( cube );

camera.position.z = 5;

function animate() {
	requestAnimationFrame( animate );

	renderer.render( scene, camera );
}
animate();