#ifndef __BoundaryModel_Akinci2012_h__
#define __BoundaryModel_Akinci2012_h__

#include "Common.h"
#include <vector>

#include "BoundaryModel.h"
#include "SPHKernels.h"
#include "FluidModel.h"


namespace SPH 
{	
	class TimeStep;

	/** \brief The boundary model stores the information required for boundary handling
	* using the approach of Akinci et al. 2012 [AIA+12].
	*
	* References:
	* - [AIA+12] Nadir Akinci, Markus Ihmsen, Gizem Akinci, Barbara Solenthaler, and Matthias Teschner. Versatile rigid-fluid coupling for incompressible SPH. ACM Trans. Graph., 31(4):62:1-62:8, July 2012. URL: http://doi.acm.org/10.1145/2185520.2185558
	*/
	class BoundaryModel_Akinci2012 : public BoundaryModel
	{
		public:
			BoundaryModel_Akinci2012();
			virtual ~BoundaryModel_Akinci2012();

		protected:
			bool m_sorted;
			unsigned int m_pointSetIndex;

			// values required for Akinci 2012 boundary handling
			std::vector<Vector3r> m_x0;
			std::vector<Vector3r> m_x;
			std::vector<Vector3r> m_v;
			std::vector<Real> m_V;
			std::vector<FieldDescription> m_fields;

			// values required for Gissler 2019 strong coupling based on Akinci 2012
			std::vector<Real> m_density;
			std::vector<Real> m_pressure;
			std::vector<Vector3r> m_v_s;
			std::vector<Real> m_s; // source term
			std::vector<Vector3r> m_v_rr;
			std::vector<Real> m_minus_rho_div_v_rr; // RHS to the source term
			Real m_density0;
			Vector3r m_v_rr_body;
			Vector3r m_omega_rr_body;

		public:
			void addField(const FieldDescription& field);
			const std::vector<FieldDescription>& getFields() {return m_fields;}
			const FieldDescription& getField(const unsigned int i) {return m_fields[i];}
			const FieldDescription& getField(const std::string& name);
			const unsigned int numberOfFields() {return static_cast<unsigned int>(m_fields.size());}
			void removeFieldByName(const std::string& fieldName);

			unsigned int numberOfParticles() const { return static_cast<unsigned int>(m_x.size()); }
			unsigned int getPointSetIndex() const { return m_pointSetIndex; }
			bool isSorted() const { return m_sorted; }

			void computeBoundaryVolume();
			void resize(const unsigned int numBoundaryParticles);

			virtual void reset();

			virtual void performNeighborhoodSearchSort();

			virtual void saveState(BinaryFileWriter &binWriter);
			virtual void loadState(BinaryFileReader &binReader);

			void initModel(RigidBodyObject *rbo, const unsigned int numBoundaryParticles, Vector3r *boundaryParticles);

			FORCE_INLINE const Real& getDensity(const Real& index) const {
				return m_density[index];
			}

			FORCE_INLINE Real& getDensity(const Real& index) {
				return m_density[index];
			}

			FORCE_INLINE void setDensity(const Real& index, const Real& value) {
				m_density[index] = value;
			}

			FORCE_INLINE const Real& getPressure(const Real& index) const {
				return m_pressure[index];
			}

			FORCE_INLINE Real& getPressure(const Real& index) {
				return m_pressure[index];
			}

			FORCE_INLINE void setPressure(const Real& index, const Real& value) {
				m_pressure[index] = value;
			}


			FORCE_INLINE const Real& getDensity0() const {
				return m_density0;
			}

			FORCE_INLINE Real& getDensity0() {
				return m_density0;
			}

			FORCE_INLINE void setDensity0(const Real& value) {
				m_density0 = value;
			}

			FORCE_INLINE const Vector3r& getV_rr_body() const {
				return m_v_rr_body;
			}

			FORCE_INLINE Vector3r& getV_rr_body() {
				return m_v_rr_body;
			}

			FORCE_INLINE void setV_rr_body(const Vector3r& value) {
				m_v_rr_body = value;
			}

			FORCE_INLINE const Vector3r& getOmega_rr_body() const {
				return m_omega_rr_body;
			}

			FORCE_INLINE Vector3r& getOmega_rr_body() {
				return m_omega_rr_body;
			}

			FORCE_INLINE void setOmega_rr_body(const Vector3r& value) {
				m_omega_rr_body = value;
			}
		
			FORCE_INLINE Vector3r &getPosition0(const unsigned int i)
			{
				return m_x0[i];
			}

			FORCE_INLINE const Vector3r &getPosition0(const unsigned int i) const
			{
				return m_x0[i];
			}

			FORCE_INLINE void setPosition0(const unsigned int i, const Vector3r &pos)
			{
				m_x0[i] = pos;
			}

			FORCE_INLINE Vector3r &getPosition(const unsigned int i)
			{
				return m_x[i];
			}

			FORCE_INLINE const Vector3r &getPosition(const unsigned int i) const
			{
				return m_x[i];
			}

			FORCE_INLINE void setPosition(const unsigned int i, const Vector3r &pos)
			{
				m_x[i] = pos;
			}

			FORCE_INLINE Vector3r &getVelocity(const unsigned int i)
			{
				return m_v[i];
			}

			FORCE_INLINE const Vector3r &getVelocity(const unsigned int i) const
			{
				return m_v[i];
			}

			FORCE_INLINE void setVelocity(const unsigned int i, const Vector3r &vel)
			{
				m_v[i] = vel;
			}

			FORCE_INLINE Vector3r& getV_s(const unsigned int i) {
				return m_v_s[i];
			}

			FORCE_INLINE const Vector3r& getV_s(const unsigned int i) const {
				return m_v_s[i];
			}

			FORCE_INLINE void setV_s(const unsigned int i, const Vector3r& value) {
				m_v_s[i] = value;
			}

			FORCE_INLINE Vector3r& getV_rr(const unsigned int i) {
				return m_v_rr[i];
			}

			FORCE_INLINE const Vector3r& getV_rr(const unsigned int i) const {
				return m_v_rr[i];
			}

			FORCE_INLINE void setV_rr(const unsigned int i, const Vector3r& value) {
				m_v_rr[i] = value;
			}

			FORCE_INLINE Real& getMinus_rho_div_v_rr(const unsigned int i) {
				return m_minus_rho_div_v_rr[i];
			}

			FORCE_INLINE const Real& getMinus_rho_div_v_rr(const unsigned int i) const {
				return m_minus_rho_div_v_rr[i];
			}

			FORCE_INLINE void setMinus_rho_div_v_rr(const unsigned int i, const Real& value) {
				m_minus_rho_div_v_rr[i] = value;
			}

			FORCE_INLINE Real& getSourceTerm(const unsigned int i) {
				return m_s[i];
			}

			FORCE_INLINE const Real& getSourceTerm(const unsigned int i) const {
				return m_s[i];
			}

			FORCE_INLINE void setSourceTerm(const unsigned int i, const Real& value) {
				m_s[i] = value;
			}

			FORCE_INLINE const Real& getVolume(const unsigned int i) const
			{
				return m_V[i];
			}

			FORCE_INLINE Real& getVolume(const unsigned int i)
			{
				return m_V[i];
			}

			FORCE_INLINE void setVolume(const unsigned int i, const Real &val)
			{
				m_V[i] = val;
			}
	};
}

#endif