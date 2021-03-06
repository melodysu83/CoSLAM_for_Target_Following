/*
 * SL_ImgPoint.h
 *
 *  Created on: 2010-11-21
 *      Author: Danping Zou
 *		E-mail: dannis.zou@gmail.com
 */

#ifndef SL_FEATUREPOINT_H_
#define SL_FEATUREPOINT_H_
#include <map>
#include <vector>

#include "math/SL_Matrix.h"
#include "geometry/SL_Point.h"

#include "SL_Camera.h"
#include "SL_Define.h"

#include "opencv2/features2d/features2d.hpp"

class MapPoint;
#define TYPE_FEATPOINT_STATIC  0
#define TYPE_FEATPOINT_DYNAMIC 1

class FeaturePoint{
public:
//	// image coordinates
//	double x, y;
//	// undistorted image coordinates
//	double ud_x, ud_y;

	union{
		struct{
			double xo, yo;	//original coordinates in the image
		};
		double mo[2];
	};
	union{
		struct{
			double x, y;	//undistorted coordinates
		};
		double m[2];
	};

	longInt id;
	//frame
	int f;
	//camera 
	int camId;
	int type;
	double reprojErr;
	//pointer to map point
	MapPoint* mpt;
	longInt mpt_id;
	//pointers to other feature points at the same frames
	FeaturePoint* pre;
	FeaturePoint* next;

	//pointer to the intrinsic matrix
	const double* K;
	//pointer to the camera pose
	CamPoseItem* cam;

	//corresponding feature points in previous and next frames 
	FeaturePoint* preFrame;
	FeaturePoint* nextFrame;

	bool bKeyFrm;

	bool mInterMatchFound;

public:
	FeaturePoint();
	~FeaturePoint();

	FeaturePoint(int f1, int camId, double x1, double y1);
	FeaturePoint(int f1, int camId, double x1, double y1, double ud_x1, double ud_y1);
	FeaturePoint(const FeaturePoint& other);
	FeaturePoint& operator=(const FeaturePoint& other);

	void setIntrinsic(const double* intrn) {
		K = intrn;
	}
	void setCameraPose(CamPoseItem* camPos) {
		cam = camPos;
	}
};
template<class FEAT_PT> 
void vecFeatPt2Mat(const std::vector<FEAT_PT*>& featPts, Mat_d& fpts){
	int nfpts = (int)featPts.size();
	fpts.resize(nfpts, 2);
	for (int i = 0; i < nfpts; i++) {
		fpts.data[2 * i] = featPts[i]->x;
		fpts.data[2 * i + 1] = featPts[i]->y;
	}
}

#endif /* SL_IMGPOINT_H_ */
