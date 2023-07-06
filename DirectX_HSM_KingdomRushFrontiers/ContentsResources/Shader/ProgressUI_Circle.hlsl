// ���̴��� ¥�ԵǸ� ������ ��Ģ�� ���Ѿ� �Ѵ�.

// 0~ 16�� ���� 
// ������ ���ٰ� ���°� �ƴϿ���.
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // �����Ͷ������� �� ��������
    // w���� ����  ����Ʈ ���ϰ� �ȼ� �������� �������� ������ ���� �����ž�.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}


OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
    
    return OutPutValue;
}

cbuffer ProgressCircleBuffer : register(b1)
{
    float4 OutColor;    
    float Progress;
}

Texture2D DiffuseTex : register(t0);
SamplerState SAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{    
    float2 Uv = _Value.UV.xy;
    float4 Color = DiffuseTex.Sample(SAMPLER, Uv);
    
    Color.xyz += OutColor.xyz;
    Color *= OutColor.a;
    
    Uv -= float2(0.5f, 0.5f);    
    
    if (Uv.x < 0)
    {
        Uv.y = -Uv.y;
    }
    
    float2 UvDir = normalize(Uv);    
    float2 DotDir = float2(0, -1);    
    
    float DotCos = acos(dot(DotDir, UvDir));
        
    if (UvDir.x < 0)
    {
        DotCos += 3.14f;
    }
    
    if (DotCos > Progress * 6.28f)
    {
        Color.a = 0.0f;
        return Color;
    }
    

    
    return Color;
}