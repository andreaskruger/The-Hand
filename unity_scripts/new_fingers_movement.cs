using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class new_fingers_movement : MonoBehaviour
{
    // Start is called before the first frame update
    // Declaring all game objects that are used in this code
    public GameObject palm;
    
    public GameObject Index_prox_phal;
    public GameObject Index_medi_phal;
    public GameObject Index_dist_phal;

    public GameObject Middle_prox_phal;
    public GameObject Middle_medi_phal;
    public GameObject Middle_dist_phal;

    public GameObject Ring_prox_phal;
    public GameObject Ring_medi_phal;
    public GameObject Ring_dist_phal;

    public GameObject Pinky_prox_phal;
    public GameObject Pinky_medi_phal;
    public GameObject Pinky_dist_phal;

    // Declaring the articulation bodies as well as the articulation drives for each finger
    private ArticulationBody a_1_body_mcp;
    private ArticulationDrive a_1_drive_mcp;
    private ArticulationDrive a_1_drive_mcp_ad;
    private ArticulationBody a_1_body_pip;
    private ArticulationDrive a_1_drive_pip;
    private ArticulationBody a_1_body_dip;
    private ArticulationDrive a_1_drive_dip;

    private ArticulationBody a_2_body_mcp;
    private ArticulationDrive a_2_drive_mcp;
    private ArticulationDrive a_2_drive_mcp_ad;
    private ArticulationBody a_2_body_pip;
    private ArticulationDrive a_2_drive_pip;
    private ArticulationBody a_2_body_dip;
    private ArticulationDrive a_2_drive_dip;

    private ArticulationBody a_3_body_mcp;
    private ArticulationDrive a_3_drive_mcp;
    private ArticulationDrive a_3_drive_mcp_ad;
    private ArticulationBody a_3_body_pip;
    private ArticulationDrive a_3_drive_pip;
    private ArticulationBody a_3_body_dip;
    private ArticulationDrive a_3_drive_dip;

    private ArticulationBody a_4_body_mcp;
    private ArticulationDrive a_4_drive_mcp;
    private ArticulationDrive a_4_drive_mcp_ad;
    private ArticulationBody a_4_body_pip;
    private ArticulationDrive a_4_drive_pip;
    private ArticulationBody a_4_body_dip;
    private ArticulationDrive a_4_drive_dip;
    
    // Variables deciding the universal stiffness and damping as well as the pip_dip_ratio
    int STIFFNESS = 1000;
    int DAMPING = 100;
    float pip_dip_ratio = 0.75f;

    private int[] serial_angles;

    void Start()
    {
        // Getting the correct objects in unity from their parent child relationship
        Index_prox_phal = palm.transform.GetChild(1).gameObject.transform.GetChild(0).gameObject;
        a_1_body_mcp = Index_prox_phal.GetComponent<ArticulationBody>();

        Index_medi_phal = Index_prox_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_1_body_pip = Index_medi_phal.GetComponent<ArticulationBody>();

        Index_dist_phal = Index_medi_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_1_body_dip = Index_dist_phal.GetComponent<ArticulationBody>();

        
        a_1_drive_mcp = a_1_body_mcp.xDrive;
        a_1_drive_mcp_ad = a_1_body_mcp.zDrive;
        a_1_drive_pip = a_1_body_pip.xDrive;
        a_1_drive_dip = a_1_body_dip.xDrive;

        a_1_drive_mcp.stiffness = STIFFNESS;
        a_1_drive_mcp_ad.stiffness = STIFFNESS;
        a_1_drive_pip.stiffness = STIFFNESS;
        a_1_drive_dip.stiffness = STIFFNESS;

        a_1_drive_mcp.damping = DAMPING;
        a_1_drive_mcp_ad.damping = DAMPING;
        a_1_drive_pip.damping = DAMPING;
        a_1_drive_dip.damping = DAMPING;

        Middle_prox_phal = palm.transform.GetChild(2).gameObject.transform.GetChild(0).gameObject;
        a_2_body_mcp = Middle_prox_phal.GetComponent<ArticulationBody>();

        Middle_medi_phal = Middle_prox_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_2_body_pip = Middle_medi_phal.GetComponent<ArticulationBody>();

        Middle_dist_phal = Middle_medi_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_2_body_dip = Middle_dist_phal.GetComponent<ArticulationBody>();

        a_2_drive_mcp = a_2_body_mcp.xDrive;
        a_2_drive_mcp_ad = a_2_body_mcp.zDrive;
        a_2_drive_pip = a_2_body_pip.xDrive;
        a_2_drive_dip = a_2_body_dip.xDrive;

        a_2_drive_mcp.stiffness = STIFFNESS;
        a_2_drive_mcp_ad.stiffness = STIFFNESS;
        a_2_drive_pip.stiffness = STIFFNESS;
        a_2_drive_dip.stiffness = STIFFNESS;

        a_2_drive_mcp.damping = DAMPING;
        a_2_drive_mcp_ad.damping = DAMPING;
        a_2_drive_pip.damping = DAMPING;
        a_2_drive_dip.damping = DAMPING;

        Ring_prox_phal = palm.transform.GetChild(3).gameObject.transform.GetChild(0).gameObject;
        a_3_body_mcp = Ring_prox_phal.GetComponent<ArticulationBody>();

        Ring_medi_phal = Ring_prox_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_3_body_pip = Ring_medi_phal.GetComponent<ArticulationBody>();

        Ring_dist_phal = Ring_medi_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_3_body_dip = Ring_dist_phal.GetComponent<ArticulationBody>();

        a_3_drive_mcp = a_3_body_mcp.xDrive;
        a_3_drive_mcp_ad = a_3_body_mcp.zDrive;
        a_3_drive_pip = a_3_body_pip.xDrive;
        a_3_drive_dip = a_3_body_dip.xDrive;

        a_3_drive_mcp.stiffness = STIFFNESS;
        a_3_drive_mcp_ad.stiffness = STIFFNESS;
        a_3_drive_pip.stiffness = STIFFNESS;
        a_3_drive_dip.stiffness = STIFFNESS;

        a_3_drive_mcp.damping = DAMPING;
        a_3_drive_mcp_ad.damping = DAMPING;
        a_3_drive_pip.damping = DAMPING;
        a_3_drive_dip.damping = DAMPING;

        Pinky_prox_phal = palm.transform.GetChild(4).gameObject.transform.GetChild(0).gameObject;
        a_4_body_mcp = Pinky_prox_phal.GetComponent<ArticulationBody>();

        Pinky_medi_phal = Pinky_prox_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_4_body_pip = Pinky_medi_phal.GetComponent<ArticulationBody>();

        Pinky_dist_phal = Pinky_medi_phal.transform.GetChild(0).gameObject.transform.GetChild(0).gameObject;
        a_4_body_dip = Pinky_dist_phal.GetComponent<ArticulationBody>();

        a_4_drive_mcp = a_4_body_mcp.xDrive;
        a_4_drive_mcp_ad = a_4_body_mcp.zDrive;
        a_4_drive_pip = a_4_body_pip.xDrive;
        a_4_drive_dip = a_4_body_dip.xDrive;

        a_4_drive_mcp.stiffness = STIFFNESS;
        a_4_drive_mcp_ad.stiffness = STIFFNESS;
        a_4_drive_pip.stiffness = STIFFNESS;
        a_4_drive_dip.stiffness = STIFFNESS;

        a_4_drive_mcp.damping = DAMPING;
        a_4_drive_mcp_ad.damping = DAMPING;
        a_4_drive_pip.damping = DAMPING;
        a_4_drive_dip.damping = DAMPING;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown("l"))
        {
            if(a_1_drive_pip.target < 110)
            {
                a_1_drive_pip.target += 10;
                a_1_drive_mcp.target += 10;

                a_2_drive_pip.target += 10;
                a_2_drive_mcp.target += 10;

                a_3_drive_pip.target += 10;
                a_3_drive_mcp.target += 10;

                a_4_drive_pip.target += 10;
                a_4_drive_mcp.target += 10;
            }

        }
        if (Input.GetKeyDown("o"))
        {
            if (a_1_drive_pip.target > -20)
            {
                a_1_drive_pip.target -= 10;
                a_1_drive_mcp.target -= 10;

                a_2_drive_pip.target -= 10;
                a_2_drive_mcp.target -= 10;

                a_3_drive_pip.target -= 10;
                a_3_drive_mcp.target -= 10;

                a_4_drive_pip.target -= 10;
                a_4_drive_mcp.target -= 10;
            }
        }

        if (Input.GetKeyDown("x"))
        {
            a_1_drive_mcp_ad.target = -25;
            a_2_drive_mcp_ad.target = -10;
            a_3_drive_mcp_ad.target = 10;
            a_4_drive_mcp_ad.target = 25;
  
        }
        if(Input.GetKeyDown("c"))
        {
            a_1_drive_mcp_ad.target = 0;
            a_2_drive_mcp_ad.target = 0;
            a_3_drive_mcp_ad.target = 0;
            a_4_drive_mcp_ad.target = 0;
        }

        a_1_drive_dip.target = a_1_drive_pip.target * pip_dip_ratio;
        a_2_drive_dip.target = a_2_drive_pip.target * pip_dip_ratio;
        a_3_drive_dip.target = a_3_drive_pip.target * pip_dip_ratio;
        a_4_drive_dip.target = a_4_drive_pip.target * pip_dip_ratio;
        

        serial_angles = serial_reader.angles;
        setFingerAngles(1, serial_angles[3], serial_angles[2], serial_angles[2] * 3 / 4, 0);
        setFingerAngles(2, serial_angles[5], serial_angles[4], serial_angles[4] * 3 / 4, 0);
        setFingerAngles(3, serial_angles[7], serial_angles[6], serial_angles[6] * 3 / 4, 0);
        setFingerAngles(4, serial_angles[9], serial_angles[8], serial_angles[8] * 3 / 4, 0);
        update_angles();
    }
    
    // This sets the angle of each joint in a given finger
    public void setFingerAngles(int finger, int mcp_angle, int pip_angle, int dip_angle, int mcp_ad_angle)
    {
        switch (finger)
        {
            case 1:
                a_1_drive_mcp.target = mcp_angle;
                a_1_drive_pip.target = pip_angle;
                a_1_drive_dip.target = dip_angle;
                a_1_drive_mcp_ad.target = mcp_ad_angle;
                break;

            case 2:
                a_2_drive_mcp.target = mcp_angle;
                a_2_drive_pip.target = pip_angle;
                a_2_drive_dip.target = dip_angle;
                a_2_drive_mcp_ad.target = mcp_ad_angle;
                break;

            case 3:
                a_3_drive_mcp.target = mcp_angle;
                a_3_drive_pip.target = pip_angle;
                a_3_drive_dip.target = dip_angle;
                a_3_drive_mcp_ad.target = mcp_ad_angle;
                break;

            case 4:
                a_4_drive_mcp.target = mcp_angle;
                a_4_drive_pip.target = pip_angle;
                a_4_drive_dip.target = dip_angle;
                a_4_drive_mcp_ad.target = mcp_ad_angle;
                break;

        }
    }

    // This updates the angles and is called at the end of each loop in the method update()
    void update_angles()
    {
        a_1_body_mcp.xDrive = a_1_drive_mcp;
        a_1_body_pip.xDrive = a_1_drive_pip;
        a_1_body_dip.xDrive = a_1_drive_dip;
        a_1_body_mcp.zDrive = a_1_drive_mcp_ad;

        a_2_body_mcp.xDrive = a_2_drive_mcp;
        a_2_body_pip.xDrive = a_2_drive_pip;
        a_2_body_dip.xDrive = a_2_drive_dip;
        a_2_body_mcp.zDrive = a_2_drive_mcp_ad;

        a_3_body_mcp.xDrive = a_3_drive_mcp;
        a_3_body_pip.xDrive = a_3_drive_pip;
        a_3_body_dip.xDrive = a_3_drive_dip;
        a_3_body_mcp.zDrive = a_3_drive_mcp_ad;

        a_4_body_mcp.xDrive = a_4_drive_mcp;
        a_4_body_pip.xDrive = a_4_drive_pip;
        a_4_body_dip.xDrive = a_4_drive_dip;
        a_4_body_mcp.zDrive = a_4_drive_mcp_ad;
    }

}