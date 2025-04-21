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
    
    // �� ������ ����� ���� ���� (���� ����ȭ)
    vec4 bleedColor = vec4(0.0);
    float totalWeight = 0.0;
    
    // 8���⸸ ���ø��Ͽ� ���� �ٻ� (���� ����)
    vec2 directions[8] = vec2[](
        vec2(1, 0), vec2(0, 1), vec2(-1, 0), vec2(0, -1),
        vec2(0.7071, 0.7071), vec2(-0.7071, 0.7071), 
        vec2(-0.7071, -0.7071), vec2(0.7071, -0.7071)
    );
    
    // ������ �ִ� �ȼ����� Ȯ��
    float centerBrightness = length(centerColor.rgb);
    bool isColoredCenter = centerBrightness > colorThreshold;
    
    // ������ �ִ� �߽� �ȼ� �ֺ����� ����
    if (isColoredCenter) {
        // �� �ȼ��� ������ �ֺ����� ������ ��
        for (int d = 0; d < 8; d++) {
            for (float dist = 1.0; dist <= bleedRadius; dist += 1.0) {
                vec2 offset = directions[d] * dist * texelSize;
                vec2 samplePos = TexCoords + offset;
                vec4 sampleColor = texture(screenTexture, samplePos);
                
                // �ֺ��� ��ο� ��쿡�� ���� ����
                float sampleBrightness = length(sampleColor.rgb);
                if (sampleBrightness < colorThreshold) {
                    // �Ÿ��� ���� ����ġ
                    float weight = 1.0 - (dist / bleedRadius);
                    weight = pow(weight, 2.0);
                    
                    bleedColor += centerColor * weight;
                    totalWeight += weight;
                }
            }
        }
    } else {
        // ��ο� �ȼ��� �ֺ� ������ ��������
        for (int d = 0; d < 8; d++) {
            for (float dist = 1.0; dist <= bleedRadius; dist += 1.0) {
                vec2 offset = directions[d] * dist * texelSize;
                vec2 samplePos = TexCoords + offset;
                vec4 sampleColor = texture(screenTexture, samplePos);
                
                // �ֺ��� ���ִ� ��� ���� ����
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
    
    // ���� ���� ���
    vec4 resultColor = centerColor;
    if (totalWeight > 0.0) {
        bleedColor /= totalWeight;
        
        // ��ο� �ȼ��� �ֺ� ���� ���� ����
        if (!isColoredCenter) {
            // �ε巯�� ����
            resultColor = mix(centerColor, bleedColor, bleedIntensity);
        }
    }
    
    finalColor = resultColor;
}
