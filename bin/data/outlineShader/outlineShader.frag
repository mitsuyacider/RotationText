#version 120

uniform sampler2DRect tex0;

uniform float u_offset;

varying vec2 texCoordVarying;

void main()
{

    float alpha=0.0;
    bool allin=true;
    for(float ix=-u_offset;ix<u_offset;ix+=1){
    for(float iy=-u_offset;iy<u_offset;iy+=1){
      float newAlpha=texture2DRect(tex0, texCoordVarying + vec2(ix, iy)).a;
      allin = allin && newAlpha>0.5;
      if(newAlpha>0.5 && newAlpha>=alpha){
        alpha=newAlpha;
      }
    }
    }
    if(allin){
    alpha=0.0;
    }
    gl_FragColor=vec4(1.0,0.0,0.0,alpha);

}
