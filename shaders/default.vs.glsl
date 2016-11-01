attribute vec2 vPos;
attribute vec2 vUV;
varying vec2 fUV;
void main()
{
    gl_Position = vec4(vPos, 0.5, 1.0);
	fUV = vec2(max(vPos.x, 0.0), max(vPos.y, 0.0));
}