// This script deals with the movements of the thumb

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class new_thumb_movements : MonoBehaviour
{
    // Declaring all game objects that are used in this code
    public GameObject poly_palm;

    public GameObject Thumb_meta_carp;
    public GameObject Thumb_prox_phal;
    public GameObject Thumb_dist_phal;

    // Declaring the articulation bodies as well as the articulation drives for each finger
    private ArticulationBody a_0_body_mcp;
    private ArticulationDrive a_0_drive_mcp;
    private ArticulationDrive a_0_drive_pip_ad;
    private ArticulationBody a_0_body_pip;
    private ArticulationDrive a_0_drive_pip;
    private ArticulationBody a_0_body_dip;
    private ArticulationDrive a_0_drive_dip;

    // Variables deciding the universal stiffness and damping as well as the pip_dip_ratio
    int STIFFNESS = 1000;
    int DAMPING = 100;

    // Start is called before the first frame update
    private int[] serial_angles = {0,0};
    void Start()
    {
        // Getting the correct objects in unity from their parent child relationship
        Thumb_meta_carp = poly_palm.transform.GetChild(0).gameObject;
        a_0_body_mcp = Thumb_meta_carp.GetComponent<ArticulationBody>();

        Thumb_prox_phal = Thumb_meta_carp.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_0_body_pip = Thumb_prox_phal.GetComponent<ArticulationBody>();

        Thumb_dist_phal = Thumb_prox_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_0_body_dip = Thumb_dist_phal.GetComponent<ArticulationBody>();


        a_0_drive_mcp = a_0_body_mcp.zDrive;
        a_0_drive_pip_ad = a_0_body_pip.zDrive;
        a_0_drive_pip = a_0_body_pip.xDrive;
        a_0_drive_dip = a_0_body_dip.xDrive;

        a_0_drive_mcp.stiffness = STIFFNESS;
        a_0_drive_pip_ad.stiffness = STIFFNESS;
        a_0_drive_pip.stiffness = STIFFNESS;
        a_0_drive_dip.stiffness = STIFFNESS;

        a_0_drive_mcp.damping = DAMPING;
        a_0_drive_pip_ad.damping = DAMPING;
        a_0_drive_pip.damping = DAMPING;
        a_0_drive_dip.damping = DAMPING;
    }

    // Update is called once per frame
    void Update()
    {
        /*
        if (Input.GetKeyDown("k"))
        {
            if (a_0_drive_mcp.target < 110)
            {
                a_0_drive_mcp.target += 10;
            }

        }
        if (Input.GetKeyDown("i"))
        {
            if (a_0_drive_mcp.target > -20)
            {
                a_0_drive_mcp.target -= 10;

            }
        }

        if (Input.GetKeyDown("u"))
        {
            if (a_0_drive_pip.target < 20)
            {
                a_0_drive_pip.target += 10;
            }

        }
        if (Input.GetKeyDown("j"))
        {
            if (a_0_drive_pip.target > -110)
            {
                a_0_drive_pip.target -= 10;

            }
        }

        if (Input.GetKeyDown("h"))
        {
            a_0_drive_pip_ad.target -= 10;

        }
        if (Input.GetKeyDown("y"))
        {
            a_0_drive_pip_ad.target += 10;

        }
        a_0_drive_dip.target = a_0_drive_pip.target * pip_dip_ratio;
        */
        serial_angles[0] = serial_reader.angles[0];
        serial_angles[1] = serial_reader.angles[1];
        setThumbAngles(0, serial_angles[1], serial_angles[0], 0);
        //setThumbAngles(0, 0, 45, 0);
        update_angles();
    }

    // This method sets the angle of all joints in the thumb to a given input
    void setThumbAngles(int tm_angle, int mcp_angle, int ip_angle, int mcp_ad_angle)
    {
        a_0_drive_mcp.target = tm_angle;
        a_0_drive_pip.target = -mcp_angle;
        a_0_drive_dip.target = -ip_angle;
        a_0_drive_pip_ad.target = mcp_ad_angle;
    }

    // This updates the angles and is called at the end of each loop in the method update()
    void update_angles()
    {
        a_0_body_mcp.zDrive = a_0_drive_mcp;
        a_0_body_pip.xDrive = a_0_drive_pip;
        a_0_body_pip.zDrive = a_0_drive_pip_ad;
        a_0_body_dip.xDrive = a_0_drive_dip;

    }
}
