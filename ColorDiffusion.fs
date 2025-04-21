#version 330 core
in vec2 TexCoords;
in vec4 fragColor;
out vec4 finalColor;
uniform sampler2D screenTexture;
uniform float bleedRadius;
uniform float bleedIntensity;
uniform float colorThreshold;

void main()
{
    vec2 texelSize = 1.0 / vec2(textureSize(screenTexture, 0));
    vec4 centerColor = texture(screenTexture, TexCoords);
    
    // 더 간단한 방식의 색상 번짐 (성능 최적화)
    vec4 bleedColor = vec4(0.0);
    float totalWeight = 0.0;
    
    // 8방향만 샘플링하여 원형 근사 (성능 개선)
    vec2 directions[8] = vec2[](
        vec2(1, 0), vec2(0, 1), vec2(-1, 0), vec2(0, -1),
        vec2(0.7071, 0.7071), vec2(-0.7071, 0.7071), 
        vec2(-0.7071, -0.7071), vec2(0.7071, -0.7071)
    );
    
    // 색상이 있는 픽셀인지 확인
    float centerBrightness = length(centerColor.rgb);
    bool isColoredCenter = centerBrightness > colorThreshold;
    
    // 색상이 있는 중심 픽셀 주변으로 번짐
    if (isColoredCenter) {
        // 이 픽셀의 색상을 주변으로 번지게 함
        for (int d = 0; d < 8; d++) {
            for (float dist = 1.0; dist <= bleedRadius; dist += 1.0) {
                vec2 offset = directions[d] * dist * texelSize;
                vec2 samplePos = TexCoords + offset;
                vec4 sampleColor = texture(screenTexture, samplePos);
                
                // 주변이 어두운 경우에만 번짐 적용
                float sampleBrightness = length(sampleColor.rgb);
                if (sampleBrightness < colorThreshold) {
                    // 거리에 따른 가중치
                    float weight = 1.0 - (dist / bleedRadius);
                    weight = pow(weight, 2.0);
                    
                    bleedColor += centerColor * weight;
                    totalWeight += weight;
                }
            }
        }
    } else {
        // 어두운 픽셀에 주변 색상이 번지도록
        for (int d = 0; d < 8; d++) {
            for (float dist = 1.0; dist <= bleedRadius; dist += 1.0) {
                vec2 offset = directions[d] * dist * texelSize;
                vec2 samplePos = TexCoords + offset;
                vec4 sampleColor = texture(screenTexture, samplePos);
                
                // 주변이 색있는 경우 번짐 적용
                float sampleBrightness = length(sampleColor.rgb);
                if (sampleBrightness > colorThreshold) {
                    float weight = 1.0 - (dist / bleedRadius);
                    weight = pow(weight, 2.0);
                    
                    bleedColor += sampleColor * weight;
                    totalWeight += weight;
                }
            }
        }
    }
    
    // 번짐 색상 계산
    vec4 resultColor = centerColor;
    if (totalWeight > 0.0) {
        bleedColor /= totalWeight;
        
        // 어두운 픽셀에 주변 색상 번짐 적용
        if (!isColoredCenter) {
            // 부드러운 블렌딩
            resultColor = mix(centerColor, bleedColor, bleedIntensity);
        }
    }
    
    finalColor = resultColor;
}
