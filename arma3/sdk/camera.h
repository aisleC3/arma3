#pragma once

class Camera
{
public:
	char pad_0000[8]; //0x0000
	Vector view_right; //0x0008
	Vector view_up; //0x0014
	Vector view_forward; //0x0020
	Vector view_trans; //0x002C
	char pad_0038[32]; //0x0038
	Vector view_size; //0x0058
	char pad_0064[108]; //0x0064
	Vector projection1; //0x00D0
	Vector projection2; //0x00DC
	char pad_00E8[152]; //0x00E8

	bool WorldToScreen(Vector in, Vector& out)
	{
		Vector d = in - view_trans;

		out.z = d.Dot(view_forward);

		if (out.z < 0.0001f)
			return false;

		float x = d.Dot(view_right);
		float y = d.Dot(view_up);

		out.x = view_size.x * (1 + (x / projection1.x / out.z));
		out.y = view_size.y * (1 - (y / projection2.y / out.z));

		return true;
	}
}; //Size: 0x0180
