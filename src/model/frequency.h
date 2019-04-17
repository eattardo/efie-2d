#ifndef __FREQUENCY_H__
#define __FREQUENCY_H__

namespace efie2d
{
/**
 * @brief      Frequency class
 */
class Frequency
{
private:
	double f; ///< frequency in Hz
	double w; ///< angular frequency omega
public:

	/**
	 * @brief      Empty ctor
	 *
	 */
	Frequency() : f(0.0), w(0.0) {};


	/**
	 * @brief      Ctor
	 *
	 * @param[in]  f    Frequency (Hz)
	 */
	Frequency(const double f);


	/**
	 * @brief      Destroys the frequency obj
	 */
	~Frequency() = default;

	/**
	 * @brief      Sets the frequency.
	 *
	 * @param[in]  f     frequency (Hz)
	 */
	void SetFrequency(const double f);


	/**
	 * @brief      Gets the frequency (Hz)
	 *
	 * @return     The frequency.
	 */
	double GetFrequency() const noexcept;


	/**
	 * @brief      Gets the angular frequency
	 *
	 * @return     w
	 */
	double GetOmega() const noexcept;
};

} // namespace efied2d


#endif /* #ifndef __FREQUENCY_H__ */