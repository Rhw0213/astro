#version 330
// �����׸�Ʈ ���̴� - ��Ʈ�� ��Ÿ���� ���ּ� �Ҳ� ȿ��
uniform float iTime;      // �ð� (�ִϸ��̼ǿ�)
uniform vec2 iResolution; // �ػ�
uniform vec2 shipPos;     // ���ּ��� ��ġ
uniform vec2 shipDir;     // ���ּ��� ���� ���� (����ȭ��)
uniform sampler2D texture0; // ���� �ؽ�ó
out vec4 fragColor;

// ������ �Լ� - �ȼ�����Ʈ�� ����� ����
float pixelNoise(vec2 uv) {
    vec2 s = floor(uv * 15.0);
    return fract(sin(s.x * 113.1 + s.y * 43.5) * 5673.0);
}

// �Ҳ� ���� ����
float flame(vec2 uv, float time, float noise) {
    // �Ҳ��� �߽��� ���
    float d = length(uv.x / 0.5);
    
    // �Ҳ� ���� (x ��ġ�� ���� y�� ����)
    float flame = 1.5 - abs(uv.y) / (0.8 + d * 0.75);
    
    // �ð��� ���� �ִϸ��̼ǰ� ������ ����
    flame += noise * 0.4 * (sin(time * 6.0 + uv.y * 10.0) * 0.2 + 0.6);
    
    // �ȼ�����Ʈ ȿ�� ���� ���� �Լ�
    return step(0.95, flame);
}

void main() {
    // ���� �ؽ�ó ���� ��������
    vec2 texCoord = gl_FragCoord.xy / iResolution.xy;
    vec4 originalColor = texture(texture0, texCoord);
    
    // ȭ�� ��ǥ ����ȭ
    vec2 uv = texCoord * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y; // ȭ�� ���� ����
    
    // ���ּ� ��ġ ����ȭ
    vec2 normalizedShipPos = shipPos / iResolution.xy;
    normalizedShipPos = normalizedShipPos * 2.0 - 1.0;
    normalizedShipPos.x *= iResolution.x / iResolution.y;
    
    // ���ּ� ���� �������� ��ǥ ȸ��
    float angle = atan(shipDir.y, shipDir.x) - radians(90.0);
    mat2 rotMat = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    vec2 rotUV = rotMat * (uv - normalizedShipPos);
    
    // �Ҳ��� ������ ���� (���ּ� ����)
    rotUV.y += 0.15;
    
    // �Ҳ� ũ�� ���� (���� Ŭ���� �Ҳ��� �۾���)
    rotUV *= 1.5;
    
    // �Ҳ� ���� ����
    if (rotUV.y < 0.0 && abs(rotUV.x) < 0.25) {
        // ��Ʈ�� ��Ÿ�� ���� �ȷ�Ʈ
        vec3 color1 = vec3(1.0, 0.3, 0.0); // ��Ȳ��
        vec3 color2 = vec3(1.0, 0.8, 0.0); // �����
        vec3 color3 = vec3(1.0, 0.1, 0.0); // ������
        
        // ������ ����
        float noise = pixelNoise(rotUV * 2.0 + iTime * 0.1);
        
        // �Ҳ� ���� ����
        float flameIntensity = flame(vec2(rotUV.x, rotUV.y), iTime, noise);
        
        // ���� �׶��̼�
        vec3 flameColor = mix(color1, color2, abs(rotUV.y * 3.0));
        flameColor = mix(flameColor, color3, noise * 0.5);
        
        // �ȼ�ȭ�� �Ҳ� ȿ�� ����
        if (flameIntensity > 0.0) {
            // ��Ʈ�� ������ ���� ���� ����ȭ
            //flameColor = floor(flameColor * 5.0) / 5.0;
            
            // �Ҳ� ���� ���� - y���� ��������(�� �Ʒ���) ������ ����
            float alpha = 1.0 - smoothstep(0.0, -0.8, rotUV.y);
            
            // �Ҳɰ� ���� �̹��� ����
            fragColor = mix(originalColor, vec4(flameColor, 1.0), alpha * flameIntensity);
            return;
        }
    }
    
    // �Ҳ��� �ƴ� ������ ���� ���� ����
    fragColor = originalColor;
}