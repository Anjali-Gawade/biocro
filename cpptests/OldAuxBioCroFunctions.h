struct ET_Str OldEvapoTrans(double Rad, double Itot, double Airtemperature,
                            double RH, double WindSpeed, double LeafAreaIndex,
                            double CanopyHeight, double StomataWS, int ws,
                            double vmax2, double alpha2, double kparm,
                            double theta, double beta, double Rd2, double b02,
                            double b12, double upperT, double lowerT,
                            double Catm);

struct ET_Str OldEvapoTrans2(double Rad, double Iave, double Airtemperature,
                             double RH, double WindSpeed, double LeafAreaIndex,
                             double CanopyHeight, double stomatacond,
                             double leafw, int eteq);
