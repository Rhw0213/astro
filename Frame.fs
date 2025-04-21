#version 330
// 프래그먼트 쉐이더 - 레트로 스타일의 우주선 불꽃 효과
uniform float iTime;      // 시간 (애니메이션용)
uniform vec2 iResolution; // 해상도
uniform vec2 shipPos;     // 우주선의 위치
uniform vec2 shipDir;     // 우주선의 방향 벡터 (정규화됨)
uniform sampler2D texture0; // 원본 텍스처
out vec4 fragColor;

// 노이즈 함수 - 픽셀레이트된 노이즈를 생성
float pixelNoise(vec2 uv) {
    vec2 s = floor(uv * 15.0);
    return fract(sin(s.x * 113.1 + s.y * 43.5) * 5673.0);
}

// 불꽃 형태 생성
float flame(vec2 uv, float time, float noise) {
    // 불꽃의 중심축 계산
    float d = length(uv.x / 0.5);
    
    // 불꽃 형태 (x 위치에 따라 y값 조절)
    float flame = 1.5 - abs(uv.y) / (0.8 + d * 0.75);
    
    // 시간에 따른 애니메이션과 노이즈 적용
    flame += noise * 0.4 * (sin(time * 6.0 + uv.y * 10.0) * 0.2 + 0.6);
    
    // 픽셀레이트 효과 위한 스텝 함수
    return step(0.95, flame);
}

void main() {
    // 원본 텍스처 색상 가져오기
    vec2 texCoord = gl_FragCoord.xy / iResolution.xy;
    vec4 originalColor = texture(texture0, texCoord);
    
    // 화면 좌표 정규화
    vec2 uv = texCoord * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y; // 화면 비율 보정
    
    // 우주선 위치 정규화
    vec2 normalizedShipPos = shipPos / iResolution.xy;
    normalizedShipPos = normalizedShipPos * 2.0 - 1.0;
    normalizedShipPos.x *= iResolution.x / iResolution.y;
    
    // 우주선 방향 기준으로 좌표 회전
    float angle = atan(shipDir.y, shipDir.x) - radians(90.0);
    mat2 rotMat = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    vec2 rotUV = rotMat * (uv - normalizedShipPos);
    
    // 불꽃의 시작점 조정 (우주선 뒤쪽)
    rotUV.y += 0.15;
    
    // 불꽃 크기 조절 (값이 클수록 불꽃이 작아짐)
    rotUV *= 1.5;
    
    // 불꽃 영역 제한
    if (rotUV.y < 0.0 && abs(rotUV.x) < 0.25) {
        // 레트로 스타일 색상 팔레트
        vec3 color1 = vec3(1.0, 0.3, 0.0); // 주황색
        vec3 color2 = vec3(1.0, 0.8, 0.0); // 노란색
        vec3 color3 = vec3(1.0, 0.1, 0.0); // 빨간색
        
        // 노이즈 생성
        float noise = pixelNoise(rotUV * 2.0 + iTime * 0.1);
        
        // 불꽃 형태 생성
        float flameIntensity = flame(vec2(rotUV.x, rotUV.y), iTime, noise);
        
        // 색상 그라데이션
        vec3 flameColor = mix(color1, color2, abs(rotUV.y * 3.0));
        flameColor = mix(flameColor, color3, noise * 0.5);
        
        // 픽셀화된 불꽃 효과 적용
        if (flameIntensity > 0.0) {
            // 레트로 느낌을 위한 색상 양자화
            //flameColor = floor(flameColor * 5.0) / 5.0;
            
            // 불꽃 길이 조절 - y값이 작을수록(더 아래쪽) 불투명도 감소
            float alpha = 1.0 - smoothstep(0.0, -0.8, rotUV.y);
            
            // 불꽃과 원본 이미지 블렌딩
            fragColor = mix(originalColor, vec4(flameColor, 1.0), alpha * flameIntensity);
            return;
        }
    }
    
    // 불꽃이 아닌 영역은 원본 색상 유지
    fragColor = originalColor;
}