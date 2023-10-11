
attribute highp vec4 qt_Vertex;
uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform highp vec4 color;
uniform highp float point_size;
void main(void)
{
   // gl_Position = vec4(qt_Vertex.x, qt_Vertex.y,qt_Vertex.z, 1.0);
    gl_PointSize = point_size;
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;

}
