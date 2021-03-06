#include "kinectbvh.h"

/**
* Constructeur
*/
KinectBVH::KinectBVH()
{
	m_nbFrame = 0;
}

/**
* Destructeur
*/
KinectBVH::~KinectBVH()
{
	m_pFile->close();
	delete m_pFile;
	m_pFile = NULL;
}

/**
* Ajoute un offset � la description du BVH
*/
void KinectBVH::AddOffset(int i, const Vector4 &offset)
{
	m_aOffsets[i].x = -offset.x * SCALE;
	m_aOffsets[i].y = offset.y * SCALE;
	m_aOffsets[i].z = offset.z * SCALE;
}

/**
* Cr�� un nouveau fichier en fonction du nom re�u en param�tre, renvoi true si r�ussi sinon false
*/
bool KinectBVH::CreateBVHFile(QString filename)
{
	m_pFile = new QFile(filename);
	if (!m_pFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}
	return true;
}

/**
* G�n�re le fichier BVH
*/
void KinectBVH::FillBVHFile()
{
	CreateSkeletonInformation();
	CreateMotionInformation();
	m_pFile->close();
	delete m_pFile;
	m_pFile = NULL;
}

/**
* G�n�re la description du squelette pour le BVH
*/
void KinectBVH::CreateSkeletonInformation()
{
	QTextStream flux(m_pFile);
	flux.setCodec("utf-8");

	// ROOT
	flux << "HIERARCHY" << endl;
	flux << "ROOT Hip" << endl;
	flux << "{" << endl;

		// Spine
		flux << "\tOFFSET " << m_aOffsets[0].x << " " << m_aOffsets[0].y << " " << m_aOffsets[0].z << endl;
		flux << "\tCHANNELS 6 Xposition Yposition Zposition Zrotation Xrotation Yrotation" << endl;
		flux << "\tJOINT Spine" << endl;
		flux << "\t{" << endl;

			// Shoulder Center
			flux << "\t\tOFFSET " << m_aOffsets[1].x - m_aOffsets[0].x << " " << m_aOffsets[1].y - m_aOffsets[0].y << " " << m_aOffsets[1].z - m_aOffsets[0].z << endl;
			flux << "\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
			flux << "\t\tJOINT ShoulderCenter" << endl;
			flux << "\t\t{" << endl;
				// Head
				flux << "\t\t\tOFFSET " << m_aOffsets[2].x - m_aOffsets[1].x << " " << m_aOffsets[2].y - m_aOffsets[1].y << " " << m_aOffsets[2].z - m_aOffsets[1].z << endl;
				flux << "\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
				flux << "\t\t\tJOINT Head" << endl;
				flux << "\t\t\t{" << endl;
					// End Site
					flux << "\t\t\t\tOFFSET " << m_aOffsets[3].x - m_aOffsets[2].x << " " << m_aOffsets[3].y - m_aOffsets[2].y << " " << m_aOffsets[3].z - m_aOffsets[2].z << endl;
					flux << "\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
					flux << "\t\t\t\tEnd Site" << endl;
					flux << "\t\t\t\t{" << endl;
						flux << "\t\t\t\t\tOFFSET 0.0 0.0 0.0" << endl;
					flux << "\t\t\t\t}" << endl;
				flux << "\t\t\t}" << endl;

				// Shoulder Left
				flux << "\t\t\tJOINT ShoulderLeft" << endl;
				flux << "\t\t\t{" << endl;
					// Elbow Left
					flux << "\t\t\t\tOFFSET " << m_aOffsets[4].x - m_aOffsets[2].x << " " << m_aOffsets[4].y - m_aOffsets[2].y << " " << m_aOffsets[4].z - m_aOffsets[2].z << endl;
					flux << "\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
					flux << "\t\t\t\tJOINT ElbowLeft" << endl;
					flux << "\t\t\t\t{" << endl;
						// Wrist Left
						flux << "\t\t\t\t\tOFFSET " << m_aOffsets[5].x - m_aOffsets[4].x << " " << m_aOffsets[5].y - m_aOffsets[4].y << " " << m_aOffsets[5].z - m_aOffsets[4].z << endl;
						flux << "\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
						flux << "\t\t\t\t\tJOINT WristLeft" << endl;
						flux << "\t\t\t\t\t{" << endl;
							// Hand Left
							flux << "\t\t\t\t\t\tOFFSET " << m_aOffsets[6].x - m_aOffsets[5].x << " " << m_aOffsets[6].y - m_aOffsets[5].y << " " << m_aOffsets[6].z - m_aOffsets[5].z << endl;
							flux << "\t\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
							flux << "\t\t\t\t\t\tJOINT HandLeft" << endl;
							flux << "\t\t\t\t\t\t{" << endl;
								// End Site
								flux << "\t\t\t\t\t\t\tOFFSET " << m_aOffsets[7].x - m_aOffsets[6].x << " " << m_aOffsets[7].y - m_aOffsets[6].y << " " << m_aOffsets[7].z - m_aOffsets[6].z << endl;
								flux << "\t\t\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
								flux << "\t\t\t\t\t\t\tEnd Site" << endl;
								flux << "\t\t\t\t\t\t\t{" << endl;
									flux << "\t\t\t\t\t\t\t\tOFFSET 0.0 0.0 0.0" << endl;
								flux << "\t\t\t\t\t\t\t}" << endl;
							flux << "\t\t\t\t\t\t}" << endl;
						flux << "\t\t\t\t\t}" << endl;
					flux << "\t\t\t\t}" << endl;
				flux << "\t\t\t}" << endl;

				// Shoulder Right
				flux << "\t\t\tJOINT ShoulderRight" << endl;
				flux << "\t\t\t{" << endl;
					// Elbow Right
					flux << "\t\t\t\tOFFSET " << m_aOffsets[8].x - m_aOffsets[2].x << " " << m_aOffsets[8].y - m_aOffsets[2].y << " " << m_aOffsets[8].z - m_aOffsets[2].z << endl;
					flux << "\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
					flux << "\t\t\t\tJOINT ElbowRight" << endl;
					flux << "\t\t\t\t{" << endl;
						// Wrist Right
						flux << "\t\t\t\t\tOFFSET " << m_aOffsets[9].x - m_aOffsets[8].x << " " << m_aOffsets[9].y - m_aOffsets[8].y << " " << m_aOffsets[9].z - m_aOffsets[8].z << endl;
						flux << "\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
						flux << "\t\t\t\t\tJOINT WristRight" << endl;
						flux << "\t\t\t\t\t{" << endl;
							// Hand Right
							flux << "\t\t\t\t\t\tOFFSET " << m_aOffsets[10].x - m_aOffsets[9].x << " " << m_aOffsets[10].y - m_aOffsets[9].y << " " << m_aOffsets[10].z - m_aOffsets[9].z << endl;
							flux << "\t\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
							flux << "\t\t\t\t\t\tJOINT HandRight" << endl;
							flux << "\t\t\t\t\t\t{" << endl;
								// End Site
								flux << "\t\t\t\t\t\t\tOFFSET " << m_aOffsets[11].x - m_aOffsets[10].x << " " << m_aOffsets[11].y - m_aOffsets[10].y << " " << m_aOffsets[11].z - m_aOffsets[10].z << endl;
								flux << "\t\t\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
								flux << "\t\t\t\t\t\t\tEnd Site" << endl;
								flux << "\t\t\t\t\t\t\t{" << endl;
									flux << "\t\t\t\t\t\t\t\tOFFSET 0.0 0.0 0.0" << endl;
								flux << "\t\t\t\t\t\t\t}" << endl;
							flux << "\t\t\t\t\t\t}" << endl;
						flux << "\t\t\t\t\t}" << endl;
					flux << "\t\t\t\t}" << endl;
				flux << "\t\t\t}" << endl;
			
			flux << "\t\t}" << endl;

		flux << "\t}" << endl;

		// Hip Left
		flux << "\tJOINT HipLeft" << endl;
		flux << "\t{" << endl;

			// Knee Left
			flux << "\t\tOFFSET " << m_aOffsets[12].x - m_aOffsets[0].x << " " << m_aOffsets[12].y - m_aOffsets[0].y << " " << m_aOffsets[12].z - m_aOffsets[0].z << endl;
			flux << "\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
			flux << "\t\tJOINT KneeLeft" << endl;
			flux << "\t\t{" << endl;

				// Ankle Left
				flux << "\t\t\tOFFSET " << m_aOffsets[13].x - m_aOffsets[12].x << " " << m_aOffsets[13].y - m_aOffsets[12].y << " " << m_aOffsets[13].z - m_aOffsets[12].z << endl;
				flux << "\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
				flux << "\t\t\tJOINT AnkleLeft" << endl;
				flux << "\t\t\t{" << endl;

					// Foot Left
					flux << "\t\t\t\tOFFSET " << m_aOffsets[14].x - m_aOffsets[13].x << " " << m_aOffsets[14].y - m_aOffsets[13].y << " " << m_aOffsets[14].z - m_aOffsets[13].z << endl;
					flux << "\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
					flux << "\t\t\t\tJOINT FootLeft" << endl;
					flux << "\t\t\t\t{" << endl;
					
						// End Site
						flux << "\t\t\t\t\tOFFSET " << m_aOffsets[15].x - m_aOffsets[14].x << " " << m_aOffsets[15].y - m_aOffsets[14].y << " " << m_aOffsets[15].z - m_aOffsets[14].z << endl;
						flux << "\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
						flux << "\t\t\t\t\tEnd Site" << endl;
						flux << "\t\t\t\t\t{" << endl;
							flux << "\t\t\t\t\t\tOFFSET 0.0 0.0 0.0" << endl;
						flux << "\t\t\t\t\t}" << endl;	
					flux << "\t\t\t\t}" << endl;
				flux << "\t\t\t}" << endl;
			flux << "\t\t}" << endl;
		flux << "\t}" << endl;

		// Hip Right
		flux << "\tJOINT HipRight" << endl;
		flux << "\t{" << endl;

			// Knee Right
			flux << "\t\tOFFSET " << m_aOffsets[16].x - m_aOffsets[0].x << " " << m_aOffsets[16].y - m_aOffsets[0].y << " " << m_aOffsets[16].z - m_aOffsets[0].z << endl;
			flux << "\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
			flux << "\t\tJOINT KneeRight" << endl;
			flux << "\t\t{" << endl;

				// Ankle Right
				flux << "\t\t\tOFFSET " << m_aOffsets[17].x - m_aOffsets[16].x << " " << m_aOffsets[17].y - m_aOffsets[16].y << " " << m_aOffsets[17].z - m_aOffsets[16].z << endl;
				flux << "\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
				flux << "\t\t\tJOINT AnkleRight" << endl;
				flux << "\t\t\t{" << endl;

					// Foot Right
					flux << "\t\t\t\tOFFSET " << m_aOffsets[18].x - m_aOffsets[17].x << " " << m_aOffsets[18].y - m_aOffsets[17].y << " " << m_aOffsets[18].z - m_aOffsets[17].z << endl;
					flux << "\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
					flux << "\t\t\t\tJOINT FootRight" << endl;
					flux << "\t\t\t\t{" << endl;
					
						// End Site
						flux << "\t\t\t\t\tOFFSET " << m_aOffsets[19].x - m_aOffsets[18].x << " " << m_aOffsets[19].y - m_aOffsets[18].y << " " << m_aOffsets[19].z - m_aOffsets[18].z << endl;
						flux << "\t\t\t\t\tCHANNELS 3 Zrotation Xrotation Yrotation" << endl;
						flux << "\t\t\t\t\tEnd Site" << endl;
						flux << "\t\t\t\t\t{" << endl;
							flux << "\t\t\t\t\t\tOFFSET 0.0 0.0 0.0" << endl;
						flux << "\t\t\t\t\t}" << endl;	
					flux << "\t\t\t\t}" << endl;
				flux << "\t\t\t}" << endl;
			flux << "\t\t}" << endl;
		flux << "\t}" << endl;

	flux << "}" << endl;
}

/**
* Incr�mente le nombre de frames
*/
void KinectBVH::IncrementNbFrames()
{
	++m_nbFrame;
}

/**
* Ajoute un squelette et ses informations pour les donn�es de la capture de mouvements
*/
void KinectBVH::AddBonesOrientation(KinectJoint *joints)
{
	m_vBonesOrientation.push_back(joints);
}

/**
* Ajoute une position du joint Hip Center pour les donn�es de la capture de mouvements
*/
void KinectBVH::AddPosition(const Vector4 &position)
{
	Vector4 pos;
	pos.x = -position.x * SCALE;
	pos.y = position.y * SCALE;
	pos.z = position.z * SCALE;
	pos.w = position.w;
	m_vPositions.push_back(pos);
}

/**
* G�n�re les donn�es des mouvements pour le BVH
*/
void KinectBVH::CreateMotionInformation()
{
	QTextStream flux(m_pFile);
	flux.setCodec("utf-8");

	flux << "\nMOTION" << endl;
	flux << "Frames: " << m_nbFrame << endl;
	flux << "Frame Time: " << FPS << endl;

	for (int i = 0; i < m_vPositions.size(); i++) {
		flux << m_vPositions[i].x << " " << m_vPositions[i].y << " " << m_vPositions[i].z << " ";
		KinectJoint *joints = m_vBonesOrientation[i];
		for(int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++) {
			Vector3f angles = joints[j].angles;
			flux << angles.z() << " " << angles.x() << " " << angles.y() << " ";
		}
		flux << endl;
	}

	m_vPositions.clear();
	m_vBonesOrientation.clear();
}

/**
* Convertis un quaternion pass� en param�tre en angles d'Euler, renvoi un tableau contenant les 3 angles
*/
int *KinectBVH::QuaternionToEulerAngles(const Vector4 &quaternion)
{
	static int eulerAngles[3] = {0, 0, 0};
	float head, pitch, roll;

	float sqw = quaternion.w * quaternion.w;
	float sqx = quaternion.x * quaternion.x;
	float sqy = quaternion.y * quaternion.y;
	float sqz = quaternion.z * quaternion.z;
	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	float test = quaternion.x * quaternion.y + quaternion.z * quaternion.w;
	if (test > 0.499 * unit) { // singularity at north pole
		eulerAngles[0] = 2 * atan2(quaternion.x, quaternion.w);
		eulerAngles[1] = PI / 2;
		eulerAngles[2] = 0;
		return eulerAngles;
	}
	if (test < -0.499 * unit) { // singularity at south pole
		eulerAngles[0] = -2 * atan2(quaternion.x, quaternion.w);
		eulerAngles[1] = -PI / 2;
		eulerAngles[2] = 0;
		return eulerAngles;
	}
	eulerAngles[0] = atan2(2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y), 1 - 2 * (sqy + sqz));
	eulerAngles[1] = asin(2 * (quaternion.w * quaternion.y - quaternion.z * quaternion.x));
	eulerAngles[2] = atan2(2 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z), 1 - 2 * (sqx + sqy));
	return eulerAngles;
}