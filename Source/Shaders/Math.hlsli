#ifndef __MATH_HLSL__
#define __MATH_HLSL__

#include "Constants.hlsli"

float3x3 CreateCoordinateSystem(in float3 N, out float3 T, out float3 B)
{
    B = float3(0.0, 1.0, 0.0);
    
    float NoUp = dot(N, float3(0.0, 1.0, 0.0));
    float epsilon = 0.0000001;
    if (1.0 - abs(NoUp) <= epsilon)
    {
        if(NoUp>0.0)
        {
            B = float3(0.0, 0.0, 1.0);
        }
        else
        {
            B = float3(0.0, 0.0, -1.0);
        }
    }
    
    T = normalize(cross(B, N));
    B = cross(N, T);
    
    return float3x3(T, B, N);
}
/*
// Sampling Disk
// Polar Mapping
float2 UniformSampleDisk(float2 u)
{
    float r = sqrt(u.x);
    float theta = 2 * PI * u.y;
    return r * float2(cos(theta), sin(theta));
}

// Concentric Mapping
float2 SampleConcentricDisk(float2 u)
{
    float2 uOffset = 2.0 * u - 1.0;

    if (uOffset.x == 0 && uOffset.y == 0)
    {
        return float2(0.0, 0.0);
    }

    float theta, r;
    if (abs(uOffset.x) > abs(uOffset.y))
    {
        r = uOffset.x;
        theta = PIOver4 * (uOffset.y / uOffset.x);
    }
    else
    {
        r = uOffset.y;
        theta = PIOver2 - PIOver4 * (uOffset.x / uOffset.y);
    }

    return r * float2(cos(theta), sin(theta));
}

// Sampling Hemisphere
float3 UniformSampleHemisphere(float2 u)
{
    float z = u.x;
    float r = sqrt(max(0.0, 1.0 - z * z));
    float phi = 2 * PI * u.y;
    return float3(r * cos(phi), r * sin(phi), z);
}

float3 UniformSampleSphere(float2 u)
{
    float z = 1.0 - 2.0 * u.x;
    float r = sqrt(max(0.0, 1.0 - z * z));
    float phi = 2 * PI * u.y;
    return float3(r * cos(phi), r * sin(phi), z);
}

float UniformHemispherePdf()
{
    return Inv2PI;
}

float3 SampleCosineHemisphere(float2 u)
{
    float2 d = SampleConcentricDisk(u);
    float z = sqrt(max(0, 1 - d.x * d.x - d.y * d.y));
    return float3(d.x, d.y, z);
}

float CosineHemispherePdf(float cosTheta)
{
    return cosTheta * InvPI;
}

// Multiple Importance Sampling
float BalanceHeuristic(int nf, float fPdf, int ng, float gPdf)
{
    return (nf * fPdf) / (nf * fPdf + ng * gPdf);
}

float PowerHeuristic(int nf, float fPdf, int ng, float gPdf)
{
    float f = nf * fPdf;
    float g = ng * gPdf;
    return (f * f) / (f * f + g * g);
}

float SphericalPhi(float3 v)
{
    float p = atan2(v.y, v.x);
    return p < 0 ? (p + 2 * PI) : p;
}

float SphericalTheta(float3 v)
{
    return acos(clamp(v.z, -1.0, 1.0));
}

float ErfInv(float x)
{
    float w, p;
    x = clamp(x, -.99999, .99999);
    w = -log((1 - x) * (1 + x));
    if (w < 5)
    {
        w = w - 2.5;
        p = 2.81022636e-08;
        p = 3.43273939e-07 + p * w;
        p = -3.5233877e-06 + p * w;
        p = -4.39150654e-06 + p * w;
        p = 0.00021858087 + p * w;
        p = -0.00125372503 + p * w;
        p = -0.00417768164 + p * w;
        p = 0.246640727 + p * w;
        p = 1.50140941 + p * w;
    }
    else
    {
        w = sqrt(w) - 3;
        p = -0.000200214257;
        p = 0.000100950558 + p * w;
        p = 0.00134934322 + p * w;
        p = -0.00367342844 + p * w;
        p = 0.00573950773 + p * w;
        p = -0.0076224613 + p * w;
        p = 0.00943887047 + p * w;
        p = 1.00167406 + p * w;
        p = 2.83297682 + p * w;
    }
    return p * x;
}

float Erf(float x)
{
	// constants
    float a1 = 0.254829592f;
    float a2 = -0.284496736f;
    float a3 = 1.421413741f;
    float a4 = -1.453152027f;
    float a5 = 1.061405429f;
    float p = 0.3275911f;

	// Save the sign of x
    int sign = 1;
    if (x < 0)
    {
        sign = -1;
    }
    x = abs(x);

	// A&S formula 7.1.26
    float t = 1 / (1 + p * x);
    float y = 1 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return sign * y;
}

float AbsCosTheta(float3 w)
{
    return abs(w.z);
}

float CosTheta(float3 w)
{
    return w.z;
}

float Cos2Theta(float3 w)
{
    return w.z * w.z;
}

float Sin2Theta(float3 w)
{
    return max(0.0, 1.0 - Cos2Theta(w));
}

float Tan2Theta(float3 w)
{
    return Sin2Theta(w) / Cos2Theta(w);
}

float SinTheta(float3 w)
{
    return sqrt(Sin2Theta(w));
}

float SinPhi(float3 w)
{
    float sinTheta = SinTheta(w);
    return sinTheta == 0.0 ? 0.0 : clamp(w.y / sinTheta, -1.0, 1.0);
}

float Sin2Phi(float3 w)
{
    return SinPhi(w) * SinPhi(w);
}

float CosPhi(float3 w)
{
    float sinTheta = SinTheta(w);
    return sinTheta == 0.0 ? 1.0 : clamp(w.x / sinTheta, -1.0, 1.0);
}

float Cos2Phi(float3 w)
{
    return CosPhi(w) * CosPhi(w);
}

float TanTheta(float3 w)
{
    return SinTheta(w) / CosTheta(w);
}

float3 SphericalDirection(float sinTheta, float cosTheta, float phi)
{
    return float3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
}

float3 Faceforward(float3 v, float3 v2)
{
    return dot(v, v2) < 0.0 ? -v : v;
}

bool SameHemisphere(float3 w, float3 wp)
{
    return w.z * wp.z > 0;
}

bool Refract(float3 wi, float3 n, float eta, out float3 wt)
{
    float cosThetaI = dot(wi, n);
    float sin2ThetaI = max(0.0, 1.0 - cosThetaI * cosThetaI);
    float sin2ThetaT = eta * eta * sin2ThetaI;

    if (sin2ThetaT >= 1.0)
    {
        return false;
    }

    float cosThetaT = sqrt(1.0 - sin2ThetaT);

    wt = eta * (-wi) + (eta * cosThetaI - cosThetaT) * n;

    return true;
}

float Radians(float deg)
{
    return PI / 180.0 * deg;
}

float Degrees(float rad)
{
    return rad * 180.0 / PI;
}

bool IsBlack(float3 v)
{
    return v.x == 0.0 && v.y == 0.0 && v.z == 0.0;
}*/

/*https://www.rorydriscoll.com/2012/01/15/cubemap-texel-solid-angle/*/
float AreaIntegration(float x, float y)
{
    return atan2(sqrt(x * x + y * y + 1), x * y);
}

float CalculateSolidAngle(uint x, uint y, uint width, uint height)
{
    float u = 2.0 * (float(x) + 0.5) / float(width) - 1.0;
    float v = 2.0 * (float(y) + 0.5) / float(height) - 1.0;

    float x0 = u - 1.0 / float(width);
    float x1 = u + 1.0 / float(width);
    float y0 = v - 1.0 / float(height);
    float y1 = v + 1.0 / float(height);

    return AreaIntegration(x0, y0) - AreaIntegration(x0, y1) - AreaIntegration(x1, y0) + AreaIntegration(x1, y1);
}

float3 CalculateCubemapDirection(uint face_idx, uint face_x, uint face_y, uint width, uint height)
{
    float u = 2.0 * (float(face_x) + 0.5) / float(width) - 1.0;
    float v = 2.0 * (float(face_y) + 0.5) / float(height) - 1.0;
    float x, y, z;

    // POSITIVE_X 0
    // NEGATIVE_X 1
    // POSITIVE_Y 2
    // NEGATIVE_Y 3
    // POSITIVE_Z 4
    // NEGATIVE_Z 5
    
    switch (face_idx)
    {
        case 0:
            x = 1;
            y = -v;
            z = -u;
            break;
        case 1:
            x = -1;
            y = -v;
            z = u;
            break;
        case 2:
            x = u;
            y = 1;
            z = v;
            break;
        case 3:
            x = u;
            y = -1;
            z = -v;
            break;
        case 4:
            x = u;
            y = -v;
            z = 1;
            break;
        case 5:
            x = -u;
            y = -v;
            z = -1;
            break;
    }

    return normalize(float3(x, y, z));
}

#endif