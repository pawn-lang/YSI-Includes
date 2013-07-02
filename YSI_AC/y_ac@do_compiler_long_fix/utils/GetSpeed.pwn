/**
 * <summary>Calculates the speed of an object using an Euclidean vector.</summary>
 * <param name="vx">X-axis of the vector.</param>
 * <param name="vy">Y-axis of the vector.</param>
 * <param name="vz">Z-axis of the vector.</param>
 * <returns>The speed.</returns>
 */
AC_STOCK Float:GetSpeed(Float:vx, Float:vy, Float:vz) {
	return floatsqroot(vx * vx + vy * vy + vz * vz)
	// Forward declaration is required because of the retrun value (float).
}
